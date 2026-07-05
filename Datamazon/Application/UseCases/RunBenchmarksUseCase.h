#pragma once
#include "../../Domain/Repositories/IProductRepository.h"
#include "../../Infrastructure/Sorting/Sorting.h"
#include <chrono>
#include <sstream>

using namespace std;

struct BenchmarkResults {
    long long linearSearchNs;
    long long avlSearchNs;
    long long hashSearchNs;
    long long mergeSortMs;
    long long quickSortMs;
    long long heapSortMs;
    int dataCount;
};

class RunBenchmarksUseCase {
private:
    IProductRepository* productRepo;

public:
    RunBenchmarksUseCase(IProductRepository* repo) {
        this->productRepo = repo;
    }

    BenchmarkResults execute() {
        BenchmarkResults res = {0};
        int n = productRepo->getAllProducts()->count();
        res.dataCount = n;
        if (n == 0) return res;

        int searchId = n / 2;
        Product* sample = productRepo->getProductById(searchId);
        string searchName = (sample) ? sample->getName() : "Laptop Pro";

        auto start = chrono::high_resolution_clock::now();
        Product* pFound = nullptr;
        Node<Product*>* curr = productRepo->getAllProducts()->head;
        while (curr != nullptr) {
            if (curr->value->getId() == searchId) {
                pFound = curr->value;
                break;
            }
            curr = curr->next;
        }
        auto end = chrono::high_resolution_clock::now();
        res.linearSearchNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        Product** ppFound = productRepo->getProductsHash()->buscar(searchId);
        end = chrono::high_resolution_clock::now();
        res.hashSearchNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        start = chrono::high_resolution_clock::now();
        Product** ppAvlFound = productRepo->getProductsAvlName()->search(searchName);
        end = chrono::high_resolution_clock::now();
        res.avlSearchNs = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        Product** arr = new Product*[n];
        curr = productRepo->getAllProducts()->head;
        for (int i = 0; i < n; i++) {
            arr[i] = curr->value;
            curr = curr->next;
        }
        start = chrono::high_resolution_clock::now();
        mergeSort(arr, 0, n - 1, [](Product* a, Product* b) { return a->getPrice() < b->getPrice(); });
        end = chrono::high_resolution_clock::now();
        res.mergeSortMs = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        delete[] arr;

        arr = new Product*[n];
        curr = productRepo->getAllProducts()->head;
        for (int i = 0; i < n; i++) {
            arr[i] = curr->value;
            curr = curr->next;
        }
        start = chrono::high_resolution_clock::now();
        quickSort(arr, 0, n - 1, [](Product* a, Product* b) { return a->getPrice() < b->getPrice(); });
        end = chrono::high_resolution_clock::now();
        res.quickSortMs = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        delete[] arr;

        arr = new Product*[n];
        curr = productRepo->getAllProducts()->head;
        for (int i = 0; i < n; i++) {
            arr[i] = curr->value;
            curr = curr->next;
        }
        start = chrono::high_resolution_clock::now();
        heapSort(arr, n, [](Product* a, Product* b) { return a->getPrice() < b->getPrice(); });
        end = chrono::high_resolution_clock::now();
        res.heapSortMs = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        delete[] arr;

        return res;
    }
};
