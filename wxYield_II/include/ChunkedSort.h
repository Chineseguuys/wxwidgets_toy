#include <vector>

#ifndef _CHUNKED_SORT_H_
#define _CHUNKED_SORT_H_

template <typename T>
struct ChunkedSort {
    ChunkedSort(std::vector<T>&& array) : mArr(array), nI(0) {}

    bool finished() {
        return nI >= (mArr.size() - 1);
    }

    bool getProgress(int scale) {
        return nI * scale / (mArr.size()  - 1);
    }

    void processChunk() {
        for (int j = 0; j < mArr.size() - nI - 1; j++) {
            if (mArr[j] > mArr[j + 1])
                std::swap(mArr[j], mArr[j + 1]);
        }
        ++nI;
    }

    std::vector<T>  mArr;
    int             nI;
};


#endif /* _CHUNKED_SORT_H_ */