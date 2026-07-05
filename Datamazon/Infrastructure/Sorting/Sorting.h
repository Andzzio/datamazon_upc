#pragma once

template <typename T, typename Compare>
void merge(T* A, int left, int mid, int right, Compare comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T* L = new T[n1];
    T* R = new T[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (comp(L[i], R[j])) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

template <typename T, typename Compare>
void mergeSort(T* A, int left, int right, Compare comp) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(A, left, mid, comp);
    mergeSort(A, mid + 1, right, comp);
    merge(A, left, mid, right, comp);
}

template <typename T, typename Compare>
int partition(T* A, int low, int high, Compare comp) {
    T pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (comp(A[j], pivot)) {
            i++;
            T temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    T temp = A[i + 1];
    A[i + 1] = A[high];
    A[high] = temp;
    return i + 1;
}

template <typename T, typename Compare>
void quickSort(T* A, int low, int high, Compare comp) {
    if (low < high) {
        int pi = partition(A, low, high, comp);
        quickSort(A, low, pi - 1, comp);
        quickSort(A, pi + 1, high, comp);
    }
}

template <typename T, typename Compare>
void heapify(T* A, int n, int i, Compare comp) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && comp(A[largest], A[l])) {
        largest = l;
    }
    if (r < n && comp(A[largest], A[r])) {
        largest = r;
    }

    if (largest != i) {
        T temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        heapify(A, n, largest, comp);
    }
}

template <typename T, typename Compare>
void heapSort(T* A, int n, Compare comp) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(A, n, i, comp);
    }
    for (int i = n - 1; i > 0; i--) {
        T temp = A[0];
        A[0] = A[i];
        A[i] = temp;
        heapify(A, i, 0, comp);
    }
}
