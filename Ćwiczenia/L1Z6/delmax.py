array = [3, 3, 3, 4, 5, 6, 7, 8]

def delmax(array):
    half = len(array) // 2
    a, b = array[:half], array[half:]
    i = len(a) - 1
    j = len(b) - 1
    result = 0
    while (i != -1):
        if (2*a[i] <= b[j]):
            result += 2
            i -= 1
            j -= 1
        else:
            i -= 1
    return result

print(delmax(array))