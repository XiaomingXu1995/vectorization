#include <stdio.h>
#include <stdlib.h>
#include "immintrin.h"
#include <stdint.h>

void print_sse_int8(__m128i a){
	int i;
	int8_t b[16];
	_mm_store_si128((__m128i *)b,a);
	for(i = 0; i < 16; i++)
		printf("%d ",b[i]);
	printf("\n");
	fflush(stdout);

	return;
}

void print_avx_int8(__m256i a){
	int i;
	int8_t b[32];
	_mm256_store_si256((__m256i *)b,a);
	for(i = 0; i < 32; i++)
		printf("%d ",b[i]);
	printf("\n");
	fflush(stdout);

	return;
}

void print_avx512_int8(__m512i a){
	int i;
	int8_t b[64];
	_mm512_store_si512((void *)b,a);
	for(i = 0; i <64; i++)
		printf("%d ",b[i]);
	printf("\n");
	fflush(stdout);

	return;
}

void print_avx512_int32(__m512i a){
	int i;
	int32_t b[16];
	_mm512_store_si512((void *)b,a);
	for(i = 0; i <16; i++)
		printf("%d ",b[i]);
	printf("\n");
	fflush(stdout);

	return;
}


int main(){
	uint32_t arr[16];
	int i;
	for(i = 0; i < 16; i++)
		arr[i]=i+1;

	__m512i varr;
	varr = _mm512_load_si512((void *) arr);
	print_avx512_int32(varr);

	__m512i vzero;
	vzero = _mm512_set1_epi32(0);

	__m512i v_result;
	v_result = _mm512_alignr_epi32(vzero,varr,1);
	print_avx512_int32(v_result);
	
}
	
