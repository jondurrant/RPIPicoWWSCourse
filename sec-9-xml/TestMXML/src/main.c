

/***
 * main.cpp - Test mxml XML Parser
 * Jon Durrant
 * 18-Mar-2024
 *
 *
 */

#include "pico/stdlib.h"
#include <stdio.h>

#include <mxml.h>
#include <pico/types.h>

int main( void )
{

	datetime_t datetime;


	stdio_init_all();
	sleep_ms(2000);
	printf("GO\n");

	const char xmlStr[] =
	"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
	"<timestamp>"
	"    <date year=\"2023\" month=\"09\" day=\"18\" />"
	"    <time hour=\"12\" minute=\"0\" second=\"0\" />"
	"</timestamp>";


	mxml_node_t *tree;
	tree = mxmlLoadString(NULL, xmlStr, MXML_OPAQUE_CALLBACK);


	mxml_node_t *node = mxmlFindElement(tree, tree, "date", NULL, NULL, MXML_DESCEND);
	char *s = mxmlElementGetAttr(node, "year");
	datetime.year = atoi(s);
	s = mxmlElementGetAttr(node, "month");
	datetime.month = atoi(s);
	s = mxmlElementGetAttr(node, "day");
	datetime.day = atoi(s);


	printf("DATE: %d-", datetime.year);
	if (datetime.month < 10){
		printf("0");
	}
	printf("%d-", datetime.month);
	if (datetime.day < 10){
		printf("0");
	}
	printf("%d\n", datetime.day);


	mxmlDelete(tree);

	printf("Done\n");

	for (;;){
		sleep_ms(3000);
	}

	return 0;
}
