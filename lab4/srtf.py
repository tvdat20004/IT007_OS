def prepareQueue (time):
    for i in range (0,numberOfProcesses,1):
        if arrivalTimeCopy[i] <= time:
            if burstTimeCopy[i] != 0:
                processDetails = [processes[i], arrivalTimeCopy[i], burstTimeCopy[i]]
                if processDetails not in queue:
                    queue.append(processDetails)
            else:
                processDetails = [processes[i],arrivalTimeCopy[i],burstTimeCopy[i]]
                if processDetails not in queue:
                    queue.append(processDetails)

def processBurstTime (currentTime):
    while burstTimeCopy[i] != 0:
        burstTimeCopy[i] -= 1
        currentTime += 1
        if currentTime not in arrivalTime:
            continue
        else:
            queue.pop(processIndex)
            prepareQueue(currentTime)
            queue.sort(key=lambda x: (x[2], x[1], x[0]))
            if processes[i] == queue[processIndex][0]:
                continue
            else:
                break
    return currentTime

inputfile = input("Enter the input file name: ")
with open(inputfile, "r") as input:
    inp = []
    for line in input.readlines():
        line = line.strip().split()
        inp.append([line[0], int(line[1]), int(line[2])])

currentTime = 0
totalTurnAroundTime = 0
totalWaitingTime = 0
numberOfProcesses = len(inp)

arrivalTime = [inp[i][1] for i in range(numberOfProcesses)]
burstTime = [inp[i][2] for i in range(numberOfProcesses)]
processes = [inp[i][0] for i in range(numberOfProcesses)]
completionTime = turnAroundTime = waitingTime = list(range(numberOfProcesses))
queue = []
arrivalTimeCopy = arrivalTime.copy()
arrivalTimeCopy1 = arrivalTime.copy()
arrivalTimeCopy.sort()
burstTimeCopy = burstTime.copy()

processIndex = 0
if arrivalTimeCopy[0] != 0:
    currentTime = arrivalTimeCopy[0]
    completionTime.append(arrivalTimeCopy[0])
    processes.append(f"//")
    prepareQueue(currentTime)
    queue.sort(key=lambda x: (x[2], x[1], x[0]))
else:
    for i in range(numberOfProcesses):
        if arrivalTimeCopy1[i] == 0:
            prepareQueue(currentTime)
            currentTime = processBurstTime(currentTime)
            if queue[processIndex][2] == 0:
                completionTime[i] = currentTime
                arrivalTimeCopy1[i] = 0
                processIndex += 1
            else:
                completionTime.append(currentTime)
                processes.append(processes[i])

while processIndex < numberOfProcesses:
    if currentTime < arrivalTimeCopy[processIndex]:
        currentTime = arrivalTimeCopy[processIndex]
        completionTime.append(arrivalTimeCopy[processIndex])
        processes.append(f"//")
        prepareQueue(currentTime)
        queue.sort(key=lambda x: (x[2], x[1], x[0]))
        processIndex -= 1
    if queue[processIndex][2] != 0:
        for i in range(0,numberOfProcesses,1):
            if queue[processIndex][0] == processes[i]:
                currentTime = processBurstTime(currentTime)
                if burstTimeCopy[i] == 0:
                    queue.pop(processIndex)
                    completionTime[i] = currentTime
                    arrivalTimeCopy1[i] = 0
                else:
                    completionTime.append(currentTime)
                    processes.append(processes[i])
                    processIndex -= 1
                prepareQueue(currentTime)
                queue.sort(key=lambda x: (x[2], x[1], x[0]))
                break
    processIndex += 1

for i in range(0,numberOfProcesses,1):
    turnAroundTime[i] = completionTime[i] - arrivalTime[i]
    waitingTime[i] = turnAroundTime[i] - burstTime[i]

completionTimeCopy = completionTime.copy()
completionTimeCopy.sort()
ganttChart = []
for i in range(0,len(completionTime),1):
    for j in range(0,len(completionTime),1):
        if completionTimeCopy[i] == completionTime[j]:
            ganttChart.append(processes[j])
print("GANTT CHART:")
print(f"0---P0", end="")
for i in range(len(completionTime)): 
    print(f"---{completionTimeCopy[i]}---{ganttChart[i]}",end="")
print()
for i in range(numberOfProcesses):
    totalTurnAroundTime+=turnAroundTime[i]
    totalWaitingTime+=waitingTime[i]
averageTurnAroundTime = totalTurnAroundTime/numberOfProcesses
averageWaitingTime = totalWaitingTime/numberOfProcesses

print(f"Average turnaround time = : {averageTurnAroundTime}")
print(f"Average waiting time: {averageWaitingTime}")

