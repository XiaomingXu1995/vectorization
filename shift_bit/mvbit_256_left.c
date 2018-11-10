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

int main(){
	uint8_t arr[32];
	int i;
	for(i = 0; i < 32; i++)
		arr[i]=i+1;
	
	__m256i varr;
	varr=_mm256_load_si256((__m256i *) arr);
	print_avx_int8(varr);

	__m256i vpermute;
	__m256i vzero,videntity;
	vzero = _mm256_set1_epi32(0);
	videntity = _mm256_set1_epi32(1);


	vpermute = _mm256_permute2x128_si256(varr, varr, 0x01);
//	print_avx_int8(vpermute);

	__m256i v_low_part;
	v_low_part = _mm256_alignr_epi8(varr,vzero,15);
//	printf("the low 16 identities:\n");
//	print_avx_int8(v_low_part);

	__m256i v_high_part_permute;
	v_high_part_permute = _mm256_alignr_epi8(vpermute,varr,15);
//	print_avx_int8(v_high_part_permute);

	__m256i v_high_part;
	v_high_part = _mm256_permute2x128_si256(v_high_part_permute,v_high_part_permute,0x01);
//	printf("the high 16 identities:\n");
//	print_avx_int8(v_high_part);

	__m256i mix_result;
	mix_result = _mm256_blend_epi32(v_high_part, v_low_part,0b00001111);
	print_avx_int8(mix_result);


}

