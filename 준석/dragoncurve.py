import copy

#기본 입출력 구현
n = int(input())

x = [0]*n
y = [0]*n
d = [0]*n
g = [0]*n

i = 0
while i < n:
    instr = input()
    parsed = instr.split()
    x[i] = int(parsed[0])
    y[i] = int(parsed[1])
    d[i] = int(parsed[2])
    g[i] = int(parsed[3])
    i = i + 1

#DC는 101*101 배열으로 저장
sum = [[0]*101 for i in range(101)]

#입력 기반으로 DC 생성
i = 0
while i < n:
    grid = [[0]*101 for i in range(101)]
    last_x = 0
    last_y = 0
    grid[x[i]][y[i]] = 1
    #d 기반으로 다음 점 찍기_naive implementation
    if d[i] == 0:
        last_x = x[i]+1
        last_y = y[i]
    elif d[i] == 1:
        last_x = x[i]
        last_y = y[i]-1
    elif d[i] == 2:
        last_x = x[i]-1
        last_y = y[i]
    elif d[i] == 3:
        last_x = x[i]
        last_y = y[i]+1
    grid[last_x][last_y] = 1
#다음 세대 = 종점 기준으로 90도 회전해 덮어쓰기
    j = 1
    while j <= g[i]:
        j = j+1
        k = 0
        grid2 = copy.deepcopy(grid)
        while k <= 100:
            l = 0
            while l <= 100:
                prev_x = l - last_y + last_x
                prev_y = last_x + last_y - k
                #범위 밖은 버리는 예외처리
                if prev_x < 0 or prev_x > 100 or prev_y < 0 or prev_y > 100 :
                    #out of bounds
                    l = l+1
                else:
                    grid[k][l] = grid2[k][l] + grid2[prev_x][prev_y]
                    l = l+1
            k = k+1
        #종점은 세대마다 바뀌므로 재계산
        temp1 = last_y + last_x - y[i]
        temp2 = x[i] - last_x + last_y
        last_x = temp1
        last_y = temp2
        '''
        #testcode
        k = 0
        while k < 10:
            l = 0
            while l < 10:
                print(grid[k][l], end='')
                l = l + 1
            print("")
            k = k + 1
        print(last_x, last_y)
        '''

    #결과 sum에 합치기
    j = 0
    while j < 101:
        k = 0
        while k < 101:
            sum[j][k] = sum[j][k] + grid[j][k]
            k = k+1
        j = j+1
    i = i + 1

#DC 전부 겹치고 1*1 사각형 검사
count = 0
i = 0
while i < 100:
    j = 0
    while j < 100:
        if sum[i][j] == 0:
            j = j + 1
        elif sum[i][j+1] == 0:
            j = j + 1
        elif sum[i+1][j] == 0:
            j = j + 1
        elif sum[i+1][j+1] == 0:
            j = j + 1
        else:
            j = j + 1
            count = count + 1
    i = i + 1

print(count)
