#ifndef _REF_BASE_H_
#define _REF_BASE_H_

// 这个类不打算做任何实现，只是为了在 shared_ptr 中进行转型使用
struct refbase {
    refbase() {
    }
};
#endif /* _REF_BASE_H_ */