#include <stdio.h>
#include <stdlib.h>
#include "immintrin.h"
#include <stdint.h>

void print_sse_int8(__m128i a){
	int i;
	int8_t b[16];
	_mm_store_si128((__m128i *)b,a);
	for(i=0;i<16;i++)
		printf("%d ",b[i]);
	printf("\n");
//	fflush(stdout);
	return;
}


void print_vec_int8(__m256i a){
	int i;
	int32_t b[8];
	_mm256_store_si256((__m256i *)b,a);
	for(i=0;i<8;i++)
		printf("%d ",b[i]);
	printf("\n");
//	fflush(stdout);
	return;
}

int main(){
	//char carr [8]={1,2,3,4,5,6,7,8};
	uint8_t carr [8]={1,2,3,4,5,6,7,8};
//	uint8_t carr[]={1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8};

//	int *result =(int *) _mm_malloc(sizeof(int)*8,64);
	__m128i vchar;
//	vchar=_mm_loadu_si64(carr);
	vchar= _mm_load_si128((__m128i*) carr);
	//print_sse_int8(vchar);
//	exit(1);
	
//	__m256i msk1;
	__m256i vint1,vint_shuffle,vint_permute;
//	vint1 =_mm256_cvtepu8_epi32(vchar);
	vint1 =_mm256_cvtepi8_epi32(vchar);
//	msk1= _mm256_set1_epi32(1);

//	int imm81=0xE4;
	int imm81=0b00011011;
	vint_shuffle= _mm256_shuffle_epi32(vint1,imm81);
	print_vec_int8(vint_shuffle);

//	int imm82=0x00;
	int imm82=0b00000011;
	vint_permute= _mm256_permute2x128_si256 (vint_shuffle,vint_shuffle,imm82);
	print_vec_int8(vint_permute);

//	_mm256_maskstore_epi32(result,msk1,vint_permute);
//	_mm256_store_si256((__m256i *)result,vint_permute);	
//	int i;
//	for(i=0;i<8;i++)
//		printf("the num is : %d \n",result[i]);
//	_mm_free(result);

}
