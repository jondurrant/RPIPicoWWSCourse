

/***
 * main.cpp -
 * Jon Durrant
 * 4-Oct-2022
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>

#include "parse_xml.h"
#include <pico/types.h>

int main( void )
{

	datetime_t datetime;
	float year;


	xs_attribute_t YEAR_ATTR = {
		.Name.String = "year",
		.Name.Length = 4,
		.Use         = EN_REQUIRED,
		.Target.Address = &datetime.year,
		.Content = EN_UINT16,
		.Content.Facet.Int.MinValue = 0,
		.Content.Facet.Int.MaxValue = 3000,
		};

	xs_attribute_t MONTH_ATTR = {
		.Name.String = "month",
		.Name.Length = 5,
		.Use         = EN_REQUIRED,
		.Target.Address = &datetime.month,
		.Content = EN_UINT8,
		.Content.Facet.Int.MinValue = 1,
		.Content.Facet.Int.MaxValue = 12,
		};

	xs_attribute_t DAY_ATTR = {
		.Name.String = "day",
		.Name.Length = 3,
		.Use         = EN_REQUIRED,
		.Target.Address = &datetime.day,
		.Content = EN_UINT8,
		.Content.Facet.Int.MinValue = 1,
		.Content.Facet.Int.MaxValue = 31,
		};

	xs_attribute_t DATE_ATTRIBUTES[] = {
			YEAR_ATTR,
			MONTH_ATTR,
			DAY_ATTR
		};

	xs_attribute_t HOUR_ATTR = {
		.Name.String = "hour",
		.Name.Length = 4,
		.Use         = EN_REQUIRED,
		.Target.Address = &datetime.hour,
		.Content = EN_UINT8,
		.Content.Facet.Int.MinValue = 0,
		.Content.Facet.Int.MaxValue = 23,
		};
	xs_attribute_t MIN_ATTR = {
		.Name.String = "minute",
		.Name.Length = 6,
		.Use         = EN_REQUIRED,
		.Target.Address = &datetime.min,
		.Content = EN_UINT8,
		.Content.Facet.Int.MinValue = 0,
		.Content.Facet.Int.MaxValue = 59,
		};
	xs_attribute_t SEC_ATTR = {
		.Name.String = "second",
		.Name.Length = 6,
		.Use         = EN_OPTIONAL,
		.Target.Address = &datetime.sec,
		.Content = EN_UINT8,
		.Content.Facet.Int.MinValue = 0,
		.Content.Facet.Int.MaxValue = 59,
		};
	xs_attribute_t TIME_ATTRIBUTES[] = {
			HOUR_ATTR,
			MIN_ATTR,
			SEC_ATTR
		};

	xs_element_t DATE_ELEMENT =
	{
		.Name.String = "date",
		.Name.Length = 4,
		.MinOccur    = 0,
		.MaxOccur    = 1,

		.Content.Type   = EN_NO_XML_DATA_TYPE,

		.Attribute_Quantity = 3,
		.Attribute          = DATE_ATTRIBUTES,
	};

	xs_element_t TIME_ELEMENT =
	{
		.Name.String = "time",
		.Name.Length = 4,
		.MinOccur    = 0,
		.MaxOccur    = 1,

		.Content.Type   = EN_NO_XML_DATA_TYPE,

		.Attribute_Quantity = 3,
		.Attribute          = TIME_ATTRIBUTES,
	};


	xs_element_t TIMESTAMP_CHILDREN[] = {DATE_ELEMENT, TIME_ELEMENT};


	xs_element_t TIMESTAMP_ELEMENT =
	{
		.Name.String = "timestamp",
		.Name.Length = 9,
		.MinOccur    = 1,
		.MaxOccur    = 1,

		.Content.Type   = EN_NO_XML_DATA_TYPE,

		 .Child_Quantity = 2,
		 .Child_Order    = EN_RANDOM,
		 .Child          = TIMESTAMP_CHILDREN ,
	};



    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

    const char xmlStr[] =
   "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    "<timestamp>"
    "    <date year=\"2023\" month=\"09\" day=\"18\" />"
    "    <time hour=\"12\" minute=\"0\" second=\"0\" />"
    "</timestamp>";


    xml_parse_result_t result = parse_xml(&TIMESTAMP_ELEMENT, xmlStr, NULL);
    printf("Result %d\n", result);

    if (result == 0){
    	printf("DATE: %d-", datetime.year);
    		if (datetime.month < 10){
    			printf("0");
    		}
    		printf("%d-", datetime.month);
    		if (datetime.day < 10){
    			printf("0");
    		}
    		printf("%d\n", datetime.day);
    }


   for (;;){
	   sleep_ms(3000);
   }

    return 0;
}
