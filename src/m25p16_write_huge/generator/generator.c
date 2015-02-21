#include <stdio.h>
#include <sys/stat.h>

#define SECTOR_SIZE 256
#define SECTOR_COUNT 4

int file_exists(const char *filename)
{
	struct stat st;
	int result = stat(filename, &st);
	return result == 0;
}

int main(int argc, char *argv[])
{
	FILE *f_in;
	unsigned char buffer[SECTOR_SIZE];
	int bytes_read, sector_id, part_id, i, j;
	
	if (argc != 2)
	{
		printf("Usage: %s <input.bin>\n", argv[0]);
		return 1;
	}
	
	if (!file_exists(argv[1]))
	{
		fprintf(stderr, "Input file does not exist, exiting.\n");
		return 2;
	}
	
	f_in = fopen(argv[1], "rb");
	if (f_in == NULL)
	{
		fprintf(stderr, "Could not open input file for reading, exiting.\n");
		return 2;
	}
	
	part_id = 0;
	j = 0;
	
	// printf("#define MEM_START 0x0000\n");
	// printf("\t\n");
	printf("#if PART == 0\n");
	
	while (1)
	{
		for (sector_id=0; sector_id<SECTOR_COUNT; sector_id++)
		{
			printf("\tuint16_t sector%d_start = MEM_START + %d;\n", sector_id, j);
			
			if (!feof(f_in))
			{
				bytes_read = fread(buffer, 1, sizeof(buffer), f_in);
				
				printf("\tuint16_t sector%d_length = %d;\n", sector_id, bytes_read);
				printf("\tstatic const uint8_t sector%d_bytes[] PROGMEM = { ", sector_id);
				for (i=0; i<bytes_read; i++)
				{
					printf("0x%02x", buffer[i]);
					if (i < bytes_read - 1)
					{
						printf(", ");
					}
				}
				printf(" };\n");
			}
			else
			{
				printf("\tuint16_t sector%d_length = 0;\n", sector_id);
				printf("\tstatic const uint8_t sector%d_bytes[] PROGMEM = {};\n", sector_id);
			}
			printf("\t\n");
			
			j++;
		}
		
		
		if (!feof(f_in))
		{
			part_id++;
			printf("#elif PART == %d\n", part_id);
		}
		else
		{
			break;
		}
	}
	fclose(f_in);
	
	printf("#else\n");
	printf("#error Invalid PART parameter.\n");
	printf("#endif\n");
	
	printf("\t\n");
	printf("\tuint16_t i;\n");
	printf("\t\n");
	printf("\t\tm25p16_init();\n");
	
	for (sector_id=0; sector_id<SECTOR_COUNT; sector_id++)
	{
		printf("\tif (sector%d_length > 0)\n", sector_id);
		printf("\t{\n");
		printf("\t\tm25p16_write_enable();\n");
		printf("\t\tm25p16_sector_erase((sector%d_start >> 8) & 0xff, sector%d_start & 0xff, 0x00);\n", sector_id, sector_id);
		printf("\t\tm25p16_wait_for_operation();\n");
		printf("\t\t\n");
		printf("\t\tm25p16_write_enable();\n");
		printf("\t\tm25p16_write_begin((sector%d_start >> 8) & 0xff, sector%d_start & 0xff, 0x00);\n", sector_id, sector_id);
		printf("\t\tfor (i=0; i<sector%d_length; i++)\n", sector_id);
		printf("\t\t{\n");
		printf("\t\t\tm25p16_write_byte(pgm_read_byte(&sector%d_bytes[i]));\n", sector_id);
		printf("\t\t}\n");
		printf("\t\tm25p16_write_end();\n");
		printf("\t\tm25p16_wait_for_operation();\n");
		printf("\t}\n");
		printf("\t\n");
	}
	
	return 0;
}
