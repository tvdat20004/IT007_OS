#include<stdio.h>

// OPT
int OptimalPageReplacement(int pages[50], int frames[5], int currentPosition, int frameCount, int pageCount) {
    int flags[5] = { 0,0,0,0,0 };
    int i;

    for (i = currentPosition + 1; i < pageCount; i++) {
        int t;
        // Đánh dấu các trang đã tồn tại trong khung
        for (t = 0; t < frameCount; t++)
            if (frames[t] == pages[i])
                flags[t] = 1;

        // Đếm số lượng trang đã tồn tại
        int flagCount = 0;
        for (t = 0; t < frameCount; t++)
            if (flags[t] == 1)
                flagCount++;

        // Nếu tất cả các trang đều tồn tại, trả về vị trí của trang hiện tại
        if (flagCount == frameCount) {
            for (t = 0; t < frameCount; t++)
                if (frames[t] == pages[i])
                    return t;
        }

        // Nếu đã duyệt hết các trang, trả về vị trí của trang chưa tồn tại
        if (i == pageCount - 1) {
            for (t = 0; t < frameCount; t++)
                if (flags[t] == 0)
                    return t;
        }
    }
    return -1;
}

// Kiểm tra xem trang đã tồn tại trong danh sách temp chưa
int IsPageExist(int page, int temp[50], int index) {
    int i;
    for (i = 0; i < index; i++)
        if (page == temp[i])
            return 1;
    return 0;
}
// LRU
int LeastRecentlyUsed(int pages[50], int frames[5], int currentPosition, int frameCount) {
    int leastRecentlyUsedIndex = -1;
    int maxDistance = currentPosition;
    
    for (int i = 0; i < frameCount; i++) {
        int lastUsed = -1;
        for (int j = currentPosition - 1; j >= 0; j--) {
            if (pages[j] == frames[i]) {
                lastUsed = j;
                break;
            }
        }
        if (lastUsed < maxDistance) {
            maxDistance = lastUsed;
            leastRecentlyUsedIndex = i;
        }
        // If a frame was never used, return it immediately
        if (lastUsed == -1) {
            return i;
        }
    }
    return leastRecentlyUsedIndex;
}
// FIFO
int FIFO(int pages[50], int frames[5], int currentPosition, int frameCount) {
    static int index = 0;
    int i;
    for (i = 0; i < frameCount; i++) {
        if (frames[i] == pages[currentPosition]) {
            return i;
        }
    }
    frames[index] = pages[currentPosition];
    index = (index + 1) % frameCount;

    return index;
}
// Hàm tạo chuỗi tham chiếu mặc định
int DefaultPageSequence(int pages[50]) {
    int pageCount = 20;
    int defaultPages[20] = { 2,2,5,2,0,2,3,5,0,0,7 };
    int i;

    for (i = 0; i < pageCount; i++)
        pages[i] = defaultPages[i];

    return pageCount;
}

// Hàm nhập chuỗi tham chiếu từ người dùng
int ManualPageSequenceInput(int pages[50]) {
    int pageCount;
    printf(" \nNhập số phần tử chuỗi tham chiếu: \n");
    scanf("%d", &pageCount);
    printf(" \nNhập vào chuỗi tham chiếu: \n");
    int i;

    for (i = 0; i < pageCount; i++)
        scanf("%d", &pages[i]);

    return pageCount;
}


int main() {
    int i, j, pageCount, pages[50], frames[5], frameCount, k, isPageAvailable, pageFaultCount = 0;
    int input;
    printf("---- - Page Replacement algorithm---- -\n");
    printf("1. Chuỗi tham chiếu mặc định.\n");
    printf("2. Nhập chuỗi tham chiếu bằng tay.\n");
    scanf("%d", &input);
    if (input == 1)
        pageCount = DefaultPageSequence(pages);
    if (input == 2)
        pageCount = ManualPageSequenceInput(pages);
    printf("\nNhập vào số khung trang :\n");
    scanf("%d", &frameCount);
    for (i = 0; i < frameCount; i++)
        frames[i] = -1;
    printf("------Page Replacement algorithm-----\n");
    printf("1. Giải thuật FIFO\n");
    printf("2. Giải thuật OPT(optimal)\n");
    printf("3. Giải thuật LRU\n");
    int algorithmChoice;
    scanf("%d", &algorithmChoice);
    if (algorithmChoice == 1)
        printf("---FIFO Page Replacement algorithm---\n");
    if (algorithmChoice == 2)
        printf("------OTP Page Replacement algorithm-----\n");
    if (algorithmChoice == 3)
        printf("------LRU Page Replacement algorithm-----\n");
    j = 0;
    printf("\t|Chuỗi|\t|Khung trang");
    for (k = 0; k < frameCount - 1; k++)
        printf("\t");
    printf("|\n");
    for (i = 0; i < pageCount; i++) {
        printf("\t|  %d  |\t", pages[i]);
        isPageAvailable = 0;
        for (k = 0; k < frameCount; k++)
            if (frames[k] == pages[i])
                isPageAvailable = 1;
        if (isPageAvailable == 0) {
            if (algorithmChoice == 1) {
                FIFO(pages, frames, i, frameCount);
                pageFaultCount++;
            } else if (algorithmChoice == 2) {
                if (i < frameCount) {
                    frames[j] = pages[i];
                    j++;
                    pageFaultCount++;
                } else {
                    int replacedIndex = OptimalPageReplacement(pages, frames, i, frameCount, pageCount);
                    if (frames[replacedIndex] != pages[i]) {
                        frames[replacedIndex] = pages[i];
                        pageFaultCount++;
                    }
                }
            } else if (algorithmChoice == 3) {
                if (i < frameCount) {
                    frames[j] = pages[i];
                    j++;
                    pageFaultCount++;
                } else {
                    int replacedIndex = LeastRecentlyUsed(pages, frames, i, frameCount);
                    if (frames[replacedIndex] != pages[i]) {
                        frames[replacedIndex] = pages[i];
                        pageFaultCount++;
                    }
                }
            }
            printf("|");
            for (k = 0; k < frameCount; k++)
                printf("%d\t", frames[k]);
            printf("| F");
        } else {
            printf("|");
            for (k = 0; k < frameCount; k++)
                printf("%d\t", frames[k]);
            printf("|");
        }
        printf("\n");
    }
    printf("Số trang lỗi là: %d\n", pageFaultCount);
    return 0;
}

