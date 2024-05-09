# Type: Shortest Job First (SJF) Scheduling Algorithm

def print_gantt_chart(gantt_chart):
    '''Print the Gantt chart to the console.'''
    seperator = "---"
    print(seperator + "Gantt Chart" + seperator)
    print(gantt_chart[0][1], end = "")
    for job in gantt_chart:
        print(seperator + job[0] + seperator + str(job[2]), end = "")
    print()

def calculate_time(jobs, gantt_chart):
    '''Calculate the response time, waiting time, and turnaround time of the processes.'''
    response_time = 0
    turnaround_time = 0
    waiting_time = 0
    checked = {"P1" : 1}
    process_endPoint = {gantt_chart[0][0] : gantt_chart[0][2]}
    for i in range(1, len(gantt_chart)):
        if gantt_chart[i][0] not in checked:
            checked[gantt_chart[i][0]] = 1
            response_time += gantt_chart[i-1][2] - gantt_chart[i][1]
        if gantt_chart[i][0] not in process_endPoint:
            process_endPoint[gantt_chart[i][0]] = gantt_chart[i][2]
            waiting_time += gantt_chart[i-1][2] - gantt_chart[i][1]
        else:
            waiting_time += gantt_chart[i-1][2] - process_endPoint[gantt_chart[i][0]]
            process_endPoint[gantt_chart[i][0]] = gantt_chart[i][2]

    turnaround_time = sum([process_endPoint[job[0]] - job[1] for job in jobs])
    print("Average response time = ", response_time / len(jobs))
    print("Average waiting time = ", waiting_time / len(jobs))
    print("Average turnaround time = ", turnaround_time / len(jobs))


def SJF(jobs):
    '''Shortest Job First (SJF) Scheduling Algorithm.'''
    # Arrange the jobs in ascending order of their burst time
    n = len(jobs)
    jobs.sort(key = lambda x: x[1])
    current_time = 0
    gantt_chart = []

    while jobs:
        # get arrived jobs
        arrived_jobs = [job for job in jobs if job[1] <= current_time]
        if arrived_jobs:
            # choose the shortest job
            shortest_job = min(arrived_jobs, key = lambda x: x[2])
            jobs.remove(shortest_job)
            current_time += shortest_job[2]
            # add the job to the Gantt chart
            gantt_chart.append((shortest_job[0], shortest_job[1], current_time))
        else:
            current_time += 1
    return gantt_chart

# read data from the input file
inputfile = input("Enter the input file name: ")
with open(inputfile, "r") as inp:
    processes = []
    for line in inp.readlines():
        line = line.strip().split()
        processes.append([line[0], int(line[1]), int(line[2])])

# create a copy of the original processes
proc = [p for p in processes]
gantt_chart = SJF(processes)
print_gantt_chart(gantt_chart)  
calculate_time(proc, gantt_chart)