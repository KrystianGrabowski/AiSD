def bubble(t):
    l = len(t)
    while l > 1:
        for i in range (0, l-1):
            if t[i] > t[i+1]:
                t[i], t[i+1] =  t[i+1],  t[i] 
        l = l - 1
    return t

print(bubble([6,5,3,1,8,7,2,4]))