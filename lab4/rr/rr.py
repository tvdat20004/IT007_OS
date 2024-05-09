def round_robin(jobs, quantum):
    '''Round Robin Scheduling Algorithm.'''
    n = len(jobs)
    jobs.sort(key=lambda x: x[1])
    current_time = 0
    gantt_chart = []
    queue = [] # jobs that are arrived but not executed
    uncompleted_job = None # job that is not completed in the quantum time
    while True:
        # get arrived jobs
        for job in jobs:
            if job[1] <= current_time:
                queue.append(job)
        jobs = [job for job in jobs if job[1] > current_time]
        
        if uncompleted_job:
            queue.append(uncompleted_job)
            uncompleted_job = None

        if not queue:
            if jobs:
                current_time += 1
            else:
                break
        else:
            job = queue.pop(0)
            if job[2] > quantum:
                current_time += quantum
                job[2] -= quantum
                uncompleted_job = job
                gantt_chart.append((job[0], job[1], current_time))
            else:
                current_time += job[2]
                job[2] = 0
                gantt_chart.append((job[0], job[1], current_time))

    return gantt_chart
def calculate_time(jobs, gantt_chart):
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
    for job in jobs:
        turnaround_time += process_endPoint[job[0]] - job[1]
    print("Average response time = ", response_time / len(jobs))
    print("Average waiting time = ", waiting_time / len(jobs))
    print("Average turnaround time = ", turnaround_time / len(jobs))

def print_gantt_chart(gantt_chart):
    separator = "---"
    print(separator + "Gantt Chart" + separator)
    print(gantt_chart[0][1], end="")
    for job in gantt_chart:
        print(separator + job[0] + separator + str(job[2]), end="")
    print()

inputfile = input("Enter the input file name: ")
quantum = int(input("Enter the time quantum: "))
with open(inputfile, "r") as inp:
    processes = []
    for line in inp.readlines():
        line = line.strip().split()
        processes.append([line[0], int(line[1]), int(line[2])])


gantt_chart = round_robin(processes, quantum)
print_gantt_chart(gantt_chart)
calculate_time(processes, gantt_chart)