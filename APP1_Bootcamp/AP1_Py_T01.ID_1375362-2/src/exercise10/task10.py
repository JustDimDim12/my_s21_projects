try:
    N, needed_time = map(int, input().split())
    apparats = []
    for i in range(N):
        year, price, time = map(int, input().split())
        apparats.append([year, price, time])
    apparats.sort(key = lambda x:x[0], reverse = True)



    right_apparats = []
    for i in range(N):
        for j in range(i+1,N):
            if apparats[i][0] == apparats[j][0] and apparats[i][2] + apparats[j][2] == needed_time:
                right_apparats.append([apparats[i][1] + apparats[j][1],apparats[i][2] + apparats[j][2]])
    print(min(right_apparats, key=lambda x:x[0])[0])
except:
    print('\nWrong Input!')