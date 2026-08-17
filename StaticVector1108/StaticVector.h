//header dosyasýnýn ayný kaynak dosyasýna birden fazla kez eklenmesini engeller.
#pragma once 

#include <cstddef>  // size_t kullanýmý icin 

// T: Veri turu ( Type )
template <typename T,std::size_t Capacity>
class StaticVector {
private: //  Dýsarýdan erisilmemesi ve sabit kalmasý gerekenler
	std::size_t count = 0;
	T arr[Capacity]{};

public: // Fonksyonlar

	bool push_back(const T& value); // Sona deger ekle 
	bool pop_back(); // Sondakini sil


	T& operator[](std::size_t index);// index bilgisi dondur
	const T& operator[](std::size_t index) const;
	

	T* at(std::size_t index); // operator ile ayný ama kontrol eder 
	const T* at(std::size_t index) const;


	std::size_t size() const;
	constexpr std::size_t capacity() const;

	T& operator[](int index)
	{
		return arr[index];
	}


	bool empty() const;
	bool full() const;
	bool exists(const T& value) const; // Aranan deger var mý 
	void clear(); // Diziyi temizle
	void print() const;


	T* back(); // En sondaki degeri goster 
	const T* back() const;


	T* front(); // En bastaki degeri goster
	const T* front() const;


	T* find(const T& value); // Aranan degeri bul
	const T* find(const T& value) const;


	bool eraseByIndex(std::size_t index); // Istenen indexteki elemaný sil
	bool insertByIndex(std::size_t index, const T& value); // Istenen indexe eleman ekle 
	
};