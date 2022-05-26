/*
    AD-SOYAD:Aleyna Dikal
    OKUL NO:B191200001
    DERS GRUP: 1-B
    ODEV NO:Programlama Dillerinin Prensibi 2.Ödev - Luhn Algoritmasının C Dilinde Uygulanması
*/

#include <stdio.h>
#include <string.h> 
#include <stdlib.h>

// her ikinci basamagin degerini iki katina cikarttigim fonksiyon
int* ikinciBasamagiIkiyleCarp(int* satirDizi, long int uzunluk) {
    // bir satirin uzunlugu kadar donecek dongu 
    for(int i = 0; i<uzunluk; i++) { 
			// sondan baslayarak her ikinci elemanin degerini 2 ile carptim
			if(i%2 == 1){
                satirDizi[uzunluk-i-1] = satirDizi[uzunluk-i-1] * 2;
            }
	}
	return satirDizi;
}
// Eger sayi 9'dan buyukse sayilari topladigim fonksiyon
void sayilariTopla(int* satirDizi,long int uzunluk) { 
	for(int i = 0; i<uzunluk; i++) {
		if(satirDizi[i] > 9){
             // 2 ile carptigimiz herhangi biri 2 basamakli ise rakamlarini topladim.
            satirDizi[i] = satirDizi[i] % 10+1;
        } 
	}
}
// Elde edilen sayilarin hepsini topladigimiz fonksiyon
int tumBasamaklariTopla(int* satirDizi) { 
	int toplam = 0;
    // Her bir satirda boşluklar silinince 16 adet rakam oldugu icin 16 kez donecek olan dongu
	for(int i = 0;i<16;i++){
        // Dizideki her bir elemani toplam değişkeni üzerinde topladığımız yer.
        toplam += satirDizi[i];
    }
	return toplam;
}


// Toplamin 10'a göre modunu alip gecerli mi gecersiz mi diye kontrol ettigimiz fonksiyon
void kartNumarasiKontrol(int toplam) { 
	if(toplam % 10 == 0){
        printf(" - gecerli");
        printf("\n");
    }
	else{
        printf(" - gecersiz");
        printf("\n");
    } 
}

// String'te yer alan bosluk karakterlerini sildigimiz fonksiyon
char *boslukKarakterleriSil(char *charDizi) { 
	int i = 0; 
    int j = 0;
	while (charDizi[i]!='\0') // bos degilse
	{
		if (charDizi[i] != ' '){
            // Boşluk karakteri haricinde olanları char dizisine ekler bu sayede boşluklar silinmiş olur.
            charDizi[j++] = charDizi[i];  
        } 
		i++;
	}
    // Char dizisinin bittiğini göstermek için eklenmiş boş karakter elemanı 
	charDizi[j] = '\0'; 
	return charDizi;
}

// string'teki satir karakterlerini sildigim metod
void satirBosluklariniSil(char* charDizi) { 
    int i = 0;
    int j = 0;
    // Dizinin elemanı boş karakter olmayana kadar devam edecek olan döngü
	while (charDizi[i]!='\0') 
	{   
        // satir karakteri ile karsilasirsa diziye almayacak
		if (charDizi[i] != '\n'){
            charDizi[j++] = charDizi[i];
        }
		i++;
	}
	charDizi[j] = '\0';
}

// Char dizisinde yer alan her elemanın int e dönüştürülüp integer array içerisine kopyalanması işlemi
int* charDonusumInt(char* karakter) { 
	
    //Karakter uzunluğunun değişkene atanmasi işlemi
    int len=strlen(karakter);
	
    // Malloc ile bellekte  yer ayirma islemi
    int *intDizi=(int*)malloc(len*sizeof(int)); 
    // Dizinin uzunlugu kadar donen for döngüsü
	for(int i=0;i<len;i++){
        // Char elemani int degere cevirdim.
        intDizi[i]=(int)karakter[i]-(int)48; 
    }
	return intDizi;
}

 // Satirdaki karakter sayisi kadar donecek ve satirlari ekrana bastiricak olan fonksiyon
void satirlariYazdir(long int uzunluk,int* satirDizi){
    for(int i=0;i<uzunluk;i++) {
			if(i %4 == 0 && i != 0){
                printf(" ");
            }  
			printf("%d", satirDizi[i]);
	}
}


int main(int argc, char *argv[]) {
    // Dosya işlemleri için oluşturulmuş File tipinde pointer değişkeni
 	FILE* dosyaPointer;
    
    // Okuduğumuz satirları atacagimiz int tipinde satirDizi arrayi
    int* satirDizi;
    
    /* Satir uzunlugu olarak varsayilan bir deger atadim 
    bu değeri seçerken her satırın uzunluğunun 19 olmasından ve 1 adet de boşluk karakteri
    okuyacağı için 21 i seçtim
    döngüler 0 dan başlıyor bu nedenle 19+1 sonrasında 1 adet '\0' karakteri 21 karakter ediyor.
    */
	int satirUzunluk = 21;

    // Her bir satırı temsil edecek string için bellekte yer ayrılması işlemi.
	char* satir = (char*) malloc(satirUzunluk*sizeof(char));

	/* Döngülerde kullanılmak üzere tutulan uzunluk değişkeni başlangıç değeri bu şekilde atanmıştır ancak daha sonradan
    while döngüsü içerisinde satirin uzunluğuna göre yeniden değer alacaktır. Çok fazla karakter alma durumu için long int 
    olarak oluşturulmuştur.
    */
	long int uzunluk = 2048; 
	
    /* Dosyanın okuma işlemi için açılması burada verilen ilk parametre dosyanın yoludur ikinci parametre ise 
    read modda açıldığını gösterir.*/
    dosyaPointer = fopen("doc/okunacak.txt", "r"); 


     // Dosyayı satır satır okuyacak while döngüsü
	while(fgets(satir, satirUzunluk, dosyaPointer)) {
        
		satirBosluklariniSil(satir);

        //Satırda olan boşluk karakterlerini silen fonksiyonun çağırılması
		boslukKarakterleriSil(satir); 
        
        

        // char dan int dönüşümü yapan fonksiyonun çağırılması
		satirDizi = charDonusumInt(satir);


        // uzunluk degiskenini dongulerde kullanmak icin tuttum. bir satirdaki rakam sayisini tutuyor
		uzunluk = strlen(satir); 
		
         // satirdaki karakter sayisi kadar donecek ve satirlari tek tek yazdiracak
        satirlariYazdir(uzunluk,satirDizi);
		
        // PDF de bize verilen algoritmanın ilk adımı
		ikinciBasamagiIkiyleCarp(satirDizi,uzunluk);

        // PDF de bize verilen algoritmanın ikinci adımı
		sayilariTopla(satirDizi,uzunluk); 
		
        // PDF de bize verilen algoritmanın üçüncü adımı
        int basamaklarinToplami = tumBasamaklariTopla(satirDizi); 
		
        // PDF de bize verilen algoritmanın dördüncü adımı
        kartNumarasiKontrol(basamaklarinToplami); 
	}

    //Açılan Dosya Okuma İşleminin Kapatılması
	fclose(dosyaPointer);

    //Oluşturulan pointerların bellekten silinmesi.
    free(satirDizi);
    free(satir);
    free(dosyaPointer);
}


