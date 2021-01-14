import math


def merge(a, left1, right1, left2, right2):
    i, j = left1, left2
    b = []
    while i <= right1 and j <= right2:
        if a[i] < a[j]:
            b.append(a[i])
            i += 1
        else:
            b.append(a[j])
            j += 1
    while i <= right1:
        b.append(a[i])
        i += 1
    while j <= right2:
        b.append(a[j])
        j += 1
    for k in range(len(b)):
        a[left1 + k] = b[k]


def mergesort(a, left, right):
    if left != right:
        middle = (left + right) // 2
        mergesort(a, left, middle)
        mergesort(a, middle + 1, right)
        merge(a, left, middle, middle + 1, right)


def partition(a, left, right):
    pivot = a[right]
    i = left - 1
    for j in range(left, right):
        if a[j] <= pivot:
            i += 1
            a[i], a[j] = a[j], a[i]
    a[i + 1], a[right] = a[right], a[i + 1]
    return i + 1


def quicksort(a, left, right):
    if left < right:
        index = partition(a, left, right)
        quicksort(a, left, index - 1)
        quicksort(a, index, right)


def select(a, left, right, i):
    if left == right:
        return a[left]
    q = partition(a, left, right)
    k = q - left + 1
    if i < k:
        return select(a, left, q - 1, i)
    elif i > k:
        return select(a, q + 1, right, i - k)
    else:
        return a[q]


def countingsort(a):
    k = max(a)
    c = [0] * k
    for i in range(len(a)):
        c[a[i] - 1] += 1
    for i in range(1, len(c)):
        c[i] += c[i - 1]
    result = [0] * len(a)
    for i in range(len(a) - 1, -1, -1):
        c[a[i] - 1] -= 1
        result[c[a[i] - 1]] = a[i]
    return result


def digits(n):
    return math.ceil(math.log10(n))


def radixsort(a):
    k = digits(max(a))
    b = []
    for i in range(len(a)):
        b.append('0' * (k - digits(a[i])) + str(a[i]))
    for i in range(k - 1, -1, -1):
        b = sorted(b, key=lambda x: int(x[i]))
    return [int(n) for n in b]


def bucketsort(a):
    b = []
    for i in range(len(a)):
        b.append([])
    for number in a:
        b[math.floor(len(a) * number)].append(number)
    result = []
    for i in range(len(b)):
        result.extend(sorted(b[i]))
    return result


class Heap:

    def __init__(self, lst):
        self.heap = []
        for value in lst:
            self.add(value)

    def swap(self, i, j):
        self.heap[i], self.heap[j] = self.heap[j], self.heap[i]

    def heapsort(self):
        lst = []
        while len(self.heap) > 0:
            lst.append(self.extract_min())
        return lst

    def min(self):
        return self.heap[0]

    def extract_min(self):
        self.swap(0, len(self.heap) - 1)
        min_element = self.heap.pop()
        self.heapify_down(0)
        return min_element

    def number_of_children(self, i):
        if 2 * i + 2 < len(self.heap):
            return 2
        if 2 * i + 1 < len(self.heap):
            return 1
        return 0

    def heapify_down(self, i):
        if self.number_of_children(i) == 2:
            if self.heap[i] > self.heap[2 * i + 1] or self.heap[i] > self.heap[2 * i + 2]:
                if self.heap[2 * i + 1] < self.heap[2 * i + 2]:
                    self.swap(i, 2 * i + 1)
                    self.heapify_down(2 * i + 1)
                else:
                    self.swap(i, 2 * i + 2)
                    self.heapify_down(2 * i + 2)
        elif self.number_of_children(i) == 1:
            if self.heap[i] > self.heap[2 * i + 1]:
                self.swap(i, 2 * i + 1)
                self.heapify_down(2 * i + 1)

    def heapify_up(self, i):
        if i != 0:
            if self.heap[i] < self.heap[(i - 1) // 2]:
                self.swap(i, (i - 1) // 2)
                self.heapify_up((i - 1) // 2)

    def add(self, value):
        self.heap.append(value)
        self.heapify_up(len(self.heap) - 1)


def sort(lst, algorithm):
    a = lst.copy()
    if algorithm == 'mergesort':
        mergesort(a, 0, len(a) - 1)
    elif algorithm == 'quicksort':
        quicksort(a, 0, len(a) - 1)
    elif algorithm == 'heapsort':
        a = Heap(a).heapsort()
    elif algorithm == 'countingsort':
        a = countingsort(a)
    elif algorithm == 'radixsort':
        a = radixsort(a)
    elif algorithm == 'bucketsort':
        a = bucketsort(a)
    return a


def binary_search(a, left, right, value):
    while (right - left + 1) > 0:
        middle = (left + right) // 2
        if a[middle] < value:
            left = middle + 1
        elif a[middle] > value:
            right = middle - 1
        else:
            return middle
    return right


a = [0, 10, 20, 30, 40, 50, 60, 70, 80]
print(binary_search(a, 0, len(a) - 1, 6))