//
// Created by solom on 4/27/2019.
//

#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <vector>
#include <fstream>

#define		DRAM_SIZE		(64*1024*1024)
#define		CACHE_SIZE		(64*1024)

enum cacheResType {MISS=0, HIT=1};

std::vector<long> L[3];

const unsigned int sample_size = 100;

unsigned int block_size, offset, t_offset[3], t[3], lvls, tmain;

unsigned int sz[3], lines[3];

unsigned int m_w = 0xABABAB55;    /* must not be zero, nor 0x464fffff */
unsigned int m_z = 0x05080902;    /* must not be zero, nor 0x9068ffff */

unsigned int rand_() {
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;  /* 32-bit result */
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

int get_tag(int lvl, unsigned int addr) {
    //offset addr to the right by byte offset and index
    return addr >> (t_offset[lvl]);
}

int get_idx(int lvl, unsigned int addr) {
    //offset by byte offset and and with index size

    return (addr >> offset) % (lines[lvl]);
}


int cacheSim(int lvl, unsigned int addr) {
    // This function accepts the memory address and returns whether it caused a cache miss or a cache hit
    // The current implementation assumes there is no cache; so, every transaction is a miss

    if (lvl >= lvls) return tmain;

    unsigned int cur_tag = get_tag(lvl, addr), cur_idx = get_idx(lvl, addr);

    if (cur_tag == L[lvl][cur_idx]) return t[lvl];

    L[lvl][cur_idx] = cur_tag;

    return t[lvl] + cacheSim(lvl + 1, addr);
}

char *msg[2] = {"Miss","Hit"};


int main() {

    block_size = 64;
    tmain = 100;
    t[0] = 11;
    offset = log2(block_size);
    sz[0] = CACHE_SIZE;
    L[0].resize(sz[0]);

    std::ofstream log("/mnt/Abdo/Abdo/Abdo's University work/Spring 2019/Assembly/Project 2/code/log.txt");

    t_offset[0] = offset + log2(sz[0] / block_size);
    sz[1] = 262144;
    L[1].resize(sz[1]);
    sz[2] = 8388608;
    L[2].resize(sz[2]);
    std::fill(L[0].begin(), L[0].end(), -1);
    for (int i = 0; i < 3; i++) {
        lines[i] = sz[i] / block_size;
    }

    cacheResType r;

    lvls = 1;

    for (int i = 0; i < sample_size; i++) {
        int addr = memGen1();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
    }

    std::fill(L[0].begin(), L[0].end(), -1);

    for (int i = 0; i < sample_size; i++) {
        int addr = memGen2();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";

    }
    std::fill(L[0].begin(), L[0].end(), -1);

    for (int i = 0; i < sample_size; i++) {
        int addr = memGen3();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
    }
    std::fill(L[0].begin(), L[0].end(), -1);


    t[0] = 4;
    t[1] = 11;

    sz[0] = 32768;
    sz[1] = 262144;

    L[0].resize(sz[0]);
    L[1].resize(sz[1]);

    lvls = 2;

    for (int i = 0; i < 2; i++) {
        lines[i] = sz[i] / block_size;
        t_offset[i] = offset + log2(sz[i] / block_size);
        std::fill(L[i].begin(), L[i].end(), -1);
    }

    for (int i = 0; i < sample_size; i++) {
        int addr = memGen1();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";

    }
    for (int i = 0; i < 2; i++) {
        std::fill(L[i].begin(), L[i].end(), -1);
    }
    for (int i = 0; i < sample_size; i++) {
        int addr = memGen2();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";

    }

    for (int i = 0; i < 2; i++) {
        std::fill(L[i].begin(), L[i].end(), -1);
    }

    for (int i = 0; i < sample_size; i++) {
        int addr = memGen3();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";

    }

    t[2] = 30;

    sz[2] = 8388608;

    L[2].resize(sz[2]);

    lvls = 3;

    for (int i = 0; i < 3; i++) {
        lines[i] = sz[i] / block_size;
        t_offset[i] = offset + log2(sz[i] / block_size);
        std::fill(L[i].begin(), L[i].end(), -1);
    }

    std::cout << cacheSim(0, 0xFF000000) << std::endl << cacheSim(0, 0xFF100000) << std::endl << cacheSim(0, 0xFF000000) << std::endl;

    std::cout << cacheSim(0, 0xf0000000) << std::endl << cacheSim(0, 0xf0006000) << std::endl << cacheSim(0, 0xf0000000) << std::endl;

    for (int i = 0; i < sample_size; i++) {
        int addr = memGen1();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";

    }

    for (int i = 0; i < 3; i++) {
        std::fill(L[i].begin(), L[i].end(), -1);
    }

    for (int i = 0; i < sample_size; i++) {
        int addr = memGen2();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";

    }

    for (int i = 0; i < 3; i++) {
        std::fill(L[i].begin(), L[i].end(), -1);
    }

    for (int i = 0; i < sample_size; i++) {
        int addr = memGen3();
        int res = cacheSim(0, addr);
        std::cout << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";
        log << "0x" << std::setfill('0') << std::setw(8) << std::dec << addr << " (" << res << ")\n";

    }

    return 0;
}