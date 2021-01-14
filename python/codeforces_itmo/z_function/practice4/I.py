def z_function(s):
    n = len(s)
    z = [0] * n
    l = r = 0
    for i in range(n):
        if i <= r:
            z[i] = min(z[i - l], r - i + 1)
        while i + z[i] < n and s[i + z[i]] == s[z[i]]:
            z[i] += 1
        if i + z[i] - 1 > r:
            l = i
            r = i + z[i] - 1
    z[0] = 0
    return z


def reverse_string(s):
    return s[::-1]


def get_occurences(p, s, k):
    m = len(p)
    a = p + "#" + s
    b = reverse_string(p) + "#" + reverse_string(s)
    z_a = z_function(a)
    z_b = z_function(b)
    occurences = []
    for i in range(m + 1, len(a) - m + 1):
        x = i - m - 1
        j = len(a) - x - m
        if z_a[i] + z_b[j] >= m - k:
            occurences.append(i - m)
    return occurences


s = input()
p = input()
k = int(input())
occurences = get_occurences(p, s, k)
print(len(occurences))
print(" ".join(map(str, occurences)))
