def z_function(s):
    n = len(s)
    z = [0] * n
    l = r = 0
    for i in range(n):
        if i <= r:
            z[i] = min(z[i - l], r - i + 1)
        while i + z[i] < n and s[i + z[i]] == s[z[i]]:
            z[i] += 1
        if z[i] + i - 1 > r:
            l = i
            r = z[i] + i - 1
    z[0] = 0
    return z


def find_sum(a, b):
    return (a + b) / 2 * (b - a + 1)


def find_length_of_all_substrings(s):
    length = 0
    t = ""
    for i in range(len(s) - 1, -1, -1):
        t = s[i] + t
        z = z_function(t)
        new_substrings = len(t) - max(z)
        length += find_sum(len(t) - new_substrings + 1, len(t))
    return length


s = input()
print(int(find_length_of_all_substrings(s)))
