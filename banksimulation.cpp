#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//YapýBaslangici-StartStruct
struct musteri{
	int musteriID;
	int musteriGiris;
	int musteriGise;
	int musteriGiseGiris;
	int musteriIslem;
	int musteriIslemSuresi;
	int musteriEnUzunBekleme;
	musteri *next;
};
typedef struct musteri mstr;

struct vezne{
	int vezneDurum;
	int vezneMusteriSayisi;
	float vezneToplamSure;
	float vezneDoluSuresi;
};
typedef struct vezne vzn;
vzn *vzn1,*vzn2,*vzn3;

struct queue{
	int kuyrukSayac;
	int topCalismaZamani;
	musteri *ilk; 
	musteri *son;
};
typedef struct queue que;
//YapýBitisi-EndStruct

//---------------------------------------

//FonksiyonPrototipleriBaslangici-StartFunctionPrototypes
int kuyrukOlustur(que *);
int kuyrukEkle(que *, int, int, int);
int vezneIslem(que *, vzn *, vzn *, vzn *);
int kuyrukSonDurum(que *);
int vezneIstatistik(que *, vzn *, vzn *, vzn *);
//FonksiyonPrototipleriBitisi-EndFunctionPrototypes

//---------------------------------------

int main(){
	srand(time(NULL));
	int stoptime;
	
	que *q = (que *) malloc(sizeof(que));
	vzn *vzn1 = (vzn *) malloc(sizeof(vzn));
	vzn *vzn2 = (vzn *) malloc(sizeof(vzn));
	vzn *vzn3 = (vzn *) malloc(sizeof(vzn));
	
	kuyrukOlustur(q);

	printf("PROGRAM CALISMA SURESI: "); scanf("%d",&stoptime);
	int musteriGelisDk,yapilacakIslem,islemSuresi,kuyrukKontrol=0;
	
	for(int i=0;i<stoptime;i++){
		musteriGelisDk=0+rand()%6+musteriGelisDk;
			if(musteriGelisDk<=stoptime){
				
				/*
				1.	EFT (3 - 10 dk)
				2.	Kredi Çekme - Withdraw Credit (10 - 20 dk)
				3.	Fatura Ödeme - Pay The Bill (2 - 12 dk)
				4.	Para Çekme - Withdraw Money (1 - 7 dk)
				*/
				islemSuresi=0;
				yapilacakIslem=1+rand()%4;
					if(yapilacakIslem==1){
						islemSuresi=3+rand()%8;
					}else if(yapilacakIslem==2){
						islemSuresi=10+rand()%11;
					}else if(yapilacakIslem==3){
						islemSuresi=2+rand()%11;
					}else if(yapilacakIslem==4){
						islemSuresi=1+rand()%7;
					}
				if(kuyrukKontrol<100){
				kuyrukEkle(q,musteriGelisDk,yapilacakIslem,islemSuresi);
				kuyrukKontrol++;
				}
			}
	}

	printf("\n---------------------------------------\n\n");
	vezneIslem(q,vzn1,vzn2,vzn3);
	printf("\n---------------------------------------\n\n");
	vezneIstatistik(q,vzn1,vzn2,vzn3);
}

//---------------------------------------

int kuyrukOlustur(que *kuyrukYapi){
	kuyrukYapi->kuyrukSayac=1;
	kuyrukYapi->ilk=NULL;
	kuyrukYapi->son=NULL;
}


int kuyrukEkle(que *q, int musteriGelisDk, int yapilacakIslem, int islemSuresi){
	mstr *temp=(mstr *) malloc(sizeof(mstr));

	char islemadi[][15]={"","EFT","Kredi Cekme","Fatura Odeme","Para Cekme"};
	int islemadi2;
	
	temp->musteriID=q->kuyrukSayac;
	temp->musteriGiris=musteriGelisDk;
	temp->musteriIslem=yapilacakIslem;
	temp->musteriIslemSuresi=islemSuresi;
	temp->next=NULL;
	q->topCalismaZamani+=islemSuresi;
	islemadi2=temp->musteriIslem;
	printf("Musteri Sira No %d, Gelis %d.Dk, Yapilacak Islem %s, Islem Suresi %d\n",temp->musteriID,temp->musteriGiris,islemadi[islemadi2],temp->musteriIslemSuresi);

	if(q->kuyrukSayac==1){
		q->ilk=temp;
		q->son=temp;
	}	
	else{
		q->son->next=temp; 
		q->son=temp;
	}
	q->kuyrukSayac++;
}

int kuyrukSonDurum(que *q){
	int topmusteri;
	
	while(q->ilk!=NULL){
		if(q==NULL){
			printf("Sira Bos.\n");
		}else{
			topmusteri++;
		}
		q->ilk=q->ilk->next;
	}
	printf("\n---------------------------------------\n\n");
	printf("Siradaki Musteri Sayisi %d\n",topmusteri);
}

int vezneIstatistik(que *q,vzn *vzn1,vzn *vzn2,vzn *vzn3){
	float v1ort,v2ort,v3ort;

	v1ort=(vzn1->vezneDoluSuresi/vzn1->vezneMusteriSayisi);
	v2ort=(vzn2->vezneDoluSuresi/vzn2->vezneMusteriSayisi);
	v3ort=(vzn3->vezneDoluSuresi/vzn3->vezneMusteriSayisi);

	printf("Gise 1 Toplam Musteri Sayisi: %d Ort. Hizmet Suresi: %0.2f dk\n",vzn1->vezneMusteriSayisi,v1ort);
	printf("Gise 2 Toplam Musteri Sayisi: %d Ort. Hizmet Suresi: %0.2f dk\n",vzn2->vezneMusteriSayisi,v2ort);
	printf("Gise 3 Toplam Musteri Sayisi: %d Ort. Hizmet Suresi: %0.2f dk\n",vzn3->vezneMusteriSayisi,v3ort);
}

int vezneIslem(que *kuyrukYapi,vzn *vzn1,vzn *vzn2,vzn *vzn3){
	int encokbekleyen1,beklemesuresi1=0,encokbekleyen2,beklemesuresi2=0,encokbekleyen3,beklemesuresi3=0,temp1,temp2,temp3;
	float GenelOrt;
	//Durum 1 ise Bos, Durum 0 ise Dolu

	for(int j=0;j<kuyrukYapi->topCalismaZamani;j++){
		if(vzn1->vezneDoluSuresi==j){
			vzn1->vezneDurum=1;
		}
		if(vzn2->vezneDoluSuresi==j){
			vzn2->vezneDurum=1;
		}
		if(vzn3->vezneDoluSuresi==j){
			vzn3->vezneDurum=1;
		}
		
		if(vzn1->vezneDurum==1 && kuyrukYapi->ilk!=NULL){
			vzn1->vezneDurum=0;
			vzn1->vezneMusteriSayisi+=1;
			vzn1->vezneDoluSuresi+=kuyrukYapi->ilk->musteriIslemSuresi;			
			kuyrukYapi->ilk->musteriGise=1;
				if(vzn1->vezneDoluSuresi>beklemesuresi1){
					encokbekleyen1=kuyrukYapi->ilk->musteriID;
					beklemesuresi1+=kuyrukYapi->ilk->musteriIslemSuresi;
					temp1=kuyrukYapi->ilk->musteriIslemSuresi;
					GenelOrt+=temp1;
				}
			printf("Gise 1 -> MUSTERI-%d, %d. dk hizmet aldi, Gise %d dk dolu kaldi. Terketme Suresi: %d dk\n",kuyrukYapi->ilk->musteriID,beklemesuresi1-temp1+kuyrukYapi->ilk->musteriGiris,kuyrukYapi->ilk->musteriIslemSuresi,beklemesuresi1);
			kuyrukYapi->ilk=kuyrukYapi->ilk->next;
		}
		if(vzn2->vezneDurum==1 && kuyrukYapi->ilk!=NULL){
			vzn2->vezneDurum=0;
			vzn2->vezneMusteriSayisi+=1;
			vzn2->vezneDoluSuresi+=kuyrukYapi->ilk->musteriIslemSuresi;			
			kuyrukYapi->ilk->musteriGise=2;
				if(vzn2->vezneDoluSuresi>beklemesuresi2){
					encokbekleyen2=kuyrukYapi->ilk->musteriID;
					beklemesuresi2+=kuyrukYapi->ilk->musteriIslemSuresi;
					temp2=kuyrukYapi->ilk->musteriIslemSuresi;
					GenelOrt+=temp2;
				}
			printf("Gise 2 -> MUSTERI-%d, %d. dk hizmet aldi, Gise %d dk dolu kaldi. Terketme Suresi: %d dk\n",kuyrukYapi->ilk->musteriID,beklemesuresi2-temp2+kuyrukYapi->ilk->musteriGiris,kuyrukYapi->ilk->musteriIslemSuresi,beklemesuresi2);
			kuyrukYapi->ilk=kuyrukYapi->ilk->next;
		}
		if(vzn3->vezneDurum==1 && kuyrukYapi->ilk!=NULL){
			vzn3->vezneDurum=0;
			vzn3->vezneMusteriSayisi+=1;
			vzn3->vezneDoluSuresi+=kuyrukYapi->ilk->musteriIslemSuresi;			
			kuyrukYapi->ilk->musteriGise=3;
				if(vzn3->vezneDoluSuresi>beklemesuresi3){
					encokbekleyen3=kuyrukYapi->ilk->musteriID;
					beklemesuresi3+=kuyrukYapi->ilk->musteriIslemSuresi;
					temp3=kuyrukYapi->ilk->musteriIslemSuresi;
					GenelOrt+=temp3;
				}	
			printf("Gise 3 -> MUSTERI-%d, %d. dk hizmet aldi, Gise %d dk dolu kaldi. Terketme Suresi: %d dk\n",kuyrukYapi->ilk->musteriID,beklemesuresi3-temp3+kuyrukYapi->ilk->musteriGiris,kuyrukYapi->ilk->musteriIslemSuresi,beklemesuresi3);
			kuyrukYapi->ilk=kuyrukYapi->ilk->next;
		}
		
	}
	GenelOrt=(float)GenelOrt/(float)(kuyrukYapi->kuyrukSayac-1);
	printf("\n---------------------------------------\n\n");
	
	if(beklemesuresi1-temp1>beklemesuresi2-temp2 && beklemesuresi1-temp1>beklemesuresi3-temp3){
		printf("En Cok Bekleyen: MUSTERI-%d, Bekleme Suresi: %d dk Terketme Suresi: %d dk\n",encokbekleyen1,beklemesuresi1-temp1,beklemesuresi1);
	}else if(beklemesuresi2-temp2>beklemesuresi1-temp1 && beklemesuresi2-temp2>beklemesuresi3-temp3){
		printf("En Cok Bekleyen: MUSTERI-%d, Bekleme Suresi: %d dk Terketme Suresi: %d dk\n",encokbekleyen2,beklemesuresi2-temp2,beklemesuresi2);
	}else if(beklemesuresi3-temp3>beklemesuresi1-temp1 && beklemesuresi3-temp3>beklemesuresi2-temp2){
		printf("En Cok Bekleyen: MUSTERI-%d, Bekleme Suresi: %d dk Terketme Suresi: %d dk\n",encokbekleyen3,beklemesuresi3-temp3,beklemesuresi3);
	}else{
		printf("\nBeklenmeyen Hata! Programý Tekrar Calistirin.!\n");
	}
	printf("\n---------------------------------------\n\n");
	printf("Bir Musterinin Kuyrukta Ort. Bekleme Suresi: %0.2f dk\n",GenelOrt);
	
	kuyrukSonDurum(kuyrukYapi);
}
