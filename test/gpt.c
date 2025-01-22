// #include <stdio.h>
// #include <pthread.h>
// #include <unistd.h>

// // Paylaşılan kaynak
// int shared_counter = 0;

// // Mutex tanımlama
// pthread_mutex_t mutex;

// // İş parçacığı fonksiyonu
// void *increment_counter(void *arg) {
// 	for (int i = 0; i < 100000; i++) {
// 		// Kilidi al
// 		pthread_mutex_lock(&mutex);

// 		// Paylaşılan kaynağı güncelle
// 		shared_counter++;

// 		// Kilidi bırak
// 		pthread_mutex_unlock(&mutex);
// 	}
// 	return NULL;
// }

// int main() {
// 	// Mutex'i başlat
// 	pthread_mutex_init(&mutex, NULL);

// 	// İş parçacıkları
// 	pthread_t thread1, thread2;

// 	// İş parçacıklarını oluştur
// 	pthread_create(&thread1, NULL, increment_counter, NULL);
// 	pthread_create(&thread2, NULL, increment_counter, NULL);

	
// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);

// 	// Son sonucu yazdır
// 	printf("Final Counter Value: %d\n", shared_counter);

// 	// Mutex'i yok et
// 	pthread_mutex_destroy(&mutex);

// 	return 0;
// }


// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// #define THREAD_COUNT 10  // Aynı anda oluşturulacak iş parçacığı sayısı
// #define MAX_COUNTER 100000000  // Sayaç değeri

// // Global sayaç
// int counter = 0;

// // Mutex
// pthread_mutex_t mutex;

// // İş parçacığı fonksiyonu
// void *increment_counter(void *arg) {
// 	while (1) {
// 		pthread_mutex_lock(&mutex); // Mutex kilitle
// 		if (counter >= MAX_COUNTER) {
// 			pthread_mutex_unlock(&mutex); // Mutex aç
// 			break;
// 		}
// 		counter++; // Sayaç artır
// 		printf("Thread %ld incremented counter to %d\n", pthread_self(), counter);
// 		pthread_mutex_unlock(&mutex); // Mutex aç
// 	}
// 	return NULL;
// }

// // Ana fonksiyon
// int main() {
// 	pthread_t threads[THREAD_COUNT]; // İş parçacıklarını tutan bir liste
// 	pthread_mutex_init(&mutex, NULL); // Mutex başlat

// 	// İş parçacıklarını oluştur
// 	for (int i = 0; i < THREAD_COUNT; i++) {
// 		if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
// 			perror("pthread_create");
// 			return EXIT_FAILURE;
// 		}
// 	}

// 	// İş parçacıklarının tamamlanmasını bekle
// 	for (int i = 0; i < THREAD_COUNT; i++) {
// 		if (pthread_join(threads[i], NULL) != 0) {
// 			perror("pthread_join");
// 			return EXIT_FAILURE;
// 		}
// 	}

// 	// Sonuçları yazdır
// 	printf("Final counter value: %d\n", counter);

// 	// Temizlik
// 	pthread_mutex_destroy(&mutex); // Mutex yok et
// 	return EXIT_SUCCESS;
// }

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Paylaşılan kaynak (değer)
int shared_value = 0;

// Mutex listesi
pthread_mutex_t mutexes[3];

// Bu fonksiyon, tüm mutex'leri kilitleyip paylaşılan değeri 100000 yapacak
void *lock_and_update(void *arg) {
	// Mutex'leri kilitle
	for (int i = 0; i < 3; i++) {
		pthread_mutex_lock(&mutexes[i]);
		printf("Mutex %d locked by thread\n", i);
	}

	// Değeri güncelle
	shared_value += 100000;
	printf("Shared value updated to %d by thread\n", shared_value);

	// Mutex'leri aç
	for (int i = 0; i < 3; i++) {
		pthread_mutex_unlock(&mutexes[i]);
		printf("Mutex %d unlocked by thread\n", i);
	}

	return NULL;
}

int main() {
	pthread_t thread1, thread2;

	// Mutex'leri başlat
	for (int i = 0; i < 3; i++) {
		pthread_mutex_init(&mutexes[i], NULL);
	}

	// İş parçacıklarını oluştur
	pthread_create(&thread1, NULL, lock_and_update, NULL);
	pthread_create(&thread2, NULL, lock_and_update, NULL);

	// İş parçacıklarının tamamlanmasını bekle
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	// Sonucu yazdır
	printf("Final Shared Value: %d\n", shared_value);

	// Mutex'leri yok et
	for (int i = 0; i < 3; i++) {
		pthread_mutex_destroy(&mutexes[i]);
	}

	return 0;
}


