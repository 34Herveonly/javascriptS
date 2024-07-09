#include <iostream>
#include <vector>

#ifndef MAIN_H
#define MAIN_H
std::vector<std::vector<int>> alloc_grid(int width, int height);
void free_grid(std::vector<std::vector<int>>& grid);
std::vector<int> arr_sum(const std::vector<int>& first, const std::vector<int>& second);
void augment_avail(std::vector<int>& available, std::vector<int>& allocated);
bool check_need(const std::vector<int>& available, const std::vector<int>& needed);
void input_arr(std::vector<int>& arr);
std::vector<std::vector<int>> input_grid(int rows, int columns);
bool full_flag(const std::vector<int>& flag);
std::vector<std::vector<int>> grid_diff(int rows, int columns, const std::vector<std::vector<int>>& max, const std::vector<std::vector<int>>& small);
std::vector<std::vector<int>> grid_sum(int rows, int columns, const std::vector<std::vector<int>>& first, const std::vector<std::vector<int>>& second);
#endif

std::vector<std::vector<int>> alloc_grid(int width, int height) {
    std::vector<std::vector<int>> s(height, std::vector<int>(width, 0));
    return s;
}

std::vector<int> arr_diff(const std::vector<int>& first, const std::vector<std::vector<int>>& second, int rows, int columns) {
    std::vector<int> arr(columns, 0);
    int i, j, sum;

    for (i = 0; i < columns; ++i) {
        sum = 0;
        for (j = 0; j < rows; ++j) {
            sum += second[i][j];
        }
        arr[i] = first[i] - sum;
    }
    return arr;
}

std::vector<int> arr_sum(const std::vector<int>& first, const std::vector<int>& second) {
    std::vector<int> arr(first.size(), 0);
    for (size_t i = 0; i < first.size(); ++i) {
        arr[i] = first[i] + second[i];
    }
    return arr;
}

void augment_avail(std::vector<int>& available, std::vector<int>& allocated) {
    for (size_t i = 0; i < available.size(); ++i) {
        available[i] += allocated[i];
        allocated[i] = 0;
    }
}

bool full_flag(const std::vector<int>& flag) {
    int sum = 0;
    for (size_t i = 0; i < flag.size(); ++i) {
        sum += flag[i];
    }
    return (sum == flag.size());
}

bool check_need(const std::vector<int>& available, const std::vector<int>& needed) {
    for (size_t i = 0; i < available.size(); ++i) {
        if (needed[i] > available[i]) {
            return false;
        }
    }
    return true;
}

void free_grid(std::vector<std::vector<int>>& grid) {
    grid.clear();
}

std::vector<std::vector<int>> grid_diff(int rows, int columns, const std::vector<std::vector<int>>& max, const std::vector<std::vector<int>>& small) {
    std::vector<std::vector<int>> grid(rows, std::vector<int>(columns, 0));
    for (int j = 0; j < rows; ++j) {
        for (int i = 0; i < columns; ++i) {
            grid[j][i] = max[j][i] - small[j][i];
        }
    }
    return grid;
}

std::vector<std::vector<int>> grid_sum(int rows, int columns, const std::vector<std::vector<int>>& first, const std::vector<std::vector<int>>& second) {
    std::vector<std::vector<int>> grid(rows, std::vector<int>(columns, 0));
    for (int j = 0; j < rows; ++j) {
        for (int i = 0; i < columns; ++i) {
            grid[j][i] = first[j][i] + second[j][i];
        }
    }
    return grid;
}

void input_arr(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << "Resource " << i + 1 << ": ";
        std::cin >> arr[i];
    }
    std::cout << std::endl;
}

std::vector<std::vector<int>> input_grid(int rows, int columns) {
    std::vector<std::vector<int>> grid(rows, std::vector<int>(columns, 0));
    for (int j = 0; j < rows; ++j) {
        for (int i = 0; i < columns; ++i) {
            std::cout << "Process " << j + 1 << " Resource " << i + 1 << ": ";
            std::cin >> grid[j][i];
        }
    }
    std::cout << std::endl;
    return grid;
}

int main() {
    std::vector<std::vector<int>> allocated, needed, maximum;
    std::vector<int> available, flags, safeS;
    int resources = 0, processes = 0, entered = 0, i = 0, j = 0, s = 0;

    std::cout << "Enter the number of processes: ";
    std::cin >> processes;
    std::cout << "Enter the number of resources: ";
    std::cin >> resources;

    available.resize(resources);
    flags.resize(processes);
    safeS.resize(processes);

    std::cout << "Enter available amount for each resource:\n";
    input_arr(available);

    std::cout << "Enter allocated resources for each process\n";
    allocated = input_grid(processes, resources);
    std::cout << "Enter maximum individual resource for each process\n";
    maximum = input_grid(processes, resources);

    needed = grid_diff(processes, resources, maximum, allocated);

    while (!full_flag(flags)) {
        i = entered = 0;
        while (i < processes) {
            if (!flags[i] && check_need(available, needed[i])) {
                j = 0;
                entered = 1;
                flags[i] = 1;
                while (j < resources) {
                    available[j] += needed[i][j];
                    j++;
                }
                safeS[s] = i + 1;
                s++;
            }
            i++;
        }
        if (!entered) {
            std::cout << "The system is in an unsafe state.\n";
            exit(0);
        }
    }

    std::cout << "The safe sequence is: ";
    i = 0;
    while (i < processes) {
        std::cout << "process_" << safeS[i] << " ";
        i++;
    }
    std::cout << std::endl;

    return 0;
}
