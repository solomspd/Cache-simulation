/*
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>

#define		DRAM_SIZE		(64*1024*1024)
#define		CACHE_SIZE		(64*1024)

enum cacheResType {MISS=0, HIT=1};

int cache[CACHE_SIZE];

const int sample_size = 1e6;

unsigned int block_size, cache_size, n_ways, offset, t_offset;

unsigned int m_w = 0xABABAB55;    // must not be zero, nor 0x464fffff
unsigned int m_z = 0x05080902;    // must not be zero, nor 0x9068ffff

unsigned int rand_() {
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  // 32-bit result
}


unsigned int memGen1() {
    static unsigned int addr=0;
    return (addr+=(16*1024))%(256*1024);
}

unsigned int memGen2() {
    static unsigned int addr=0;
    return (addr+=4)%(DRAM_SIZE);
}

unsigned int memGen3() {
    return rand_()%(256*1024);
}

int get_tag(int addr) {
    //offset addr to the right by byte offset and index
    return addr >> (t_offset);
}

int get_idx(int addr) {
    //offset by byte offset and and with index size

    return (addr >> offset) % (cache_size/block_size);
}

// Cache Simulator
cacheResType cacheSim(unsigned int addr) {
    // This function accepts the memory address and returns whether it caused a cache miss or a cache hit
    // The current implementation assumes there is no cache; so, every transaction is a miss

    // code for direct mapping

    unsigned int cur_tag = get_tag(addr), cur_idx = get_idx(addr);
    if (cur_tag == cache[cur_idx]) return HIT;

    cache[cur_idx] = cur_tag;

    return MISS;
}

char *msg[2] = {"Miss","Hit"};

int main() {
    int iter;

    cacheResType r;

    memset(cache, -1, sizeof cache);

    unsigned int addr;
    std::cout << "Cache Simulator\n";
    // change the number of iterations into a minimum of 1,000,000

    //exp 1
    cache_size = CACHE_SIZE;
    block_size = 4;
    n_ways = 0;


    while (block_size <= 128) {
        memset(cache, -1, sizeof cache);
        offset = log2(block_size);
        t_offset = offset + log2(cache_size / block_size);
        for (iter = 0; iter < 100; iter++) {
            addr = memGen1();
            r = cacheSim(addr);
            std::cout << "0x" << std::setfill('0') << std::setw(8) << std::hex << addr << " (" << msg[r] << ")\n";
        }
        block_size *= 2;
    }

    while (block_size <= 128) {
        memset(cache, -1, sizeof cache);
        offset = log2(block_size);
        t_offset = offset + log2(cache_size / block_size);
        for (iter = 0; iter < 100; iter++) {
            addr = memGen2();
            r = cacheSim(addr);
            std::cout << "0x" << std::setfill('0') << std::setw(8) << std::hex << addr << " (" << msg[r] << ")\n";
        }
        block_size *= 2;
    }

    while (block_size <= 128) {
        memset(cache, -1, sizeof cache);
        offset = log2(block_size);
        t_offset = offset + log2(cache_size / block_size);
        for (iter = 0; iter < 100; iter++) {
            addr = memGen3();
            r = cacheSim(addr);
            std::cout << "0x" << std::setfill('0') << std::setw(8) << std::hex << addr << " (" << msg[r] << ")\n";
        }
        block_size *= 2;
    }

    std::cin.get();
    return 0;
}
*/