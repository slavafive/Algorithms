def get_z_function(str):
    z = [0] * len(str)
    z[0] = 0
    for i in range(1, len(str)):
        while z[i] + i < len(str) and str[z[i]] == str[z[i] + i]:
            z[i] += 1
    return z


s = input()
z = get_z_function(s)
print(" ".join(map(str, z)))