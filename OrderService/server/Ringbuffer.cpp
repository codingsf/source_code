
#include "Ringbuffer.h"
#include <iostream>
#include <cstring>
#include <cassert>

XRingBuffer::XRingBuffer(const DWORD size) : _size(size + XRING_BUFFER_READ_POS_AND_WRITE_POS_SIZE),
                                             _buffer(new char[_size]),_write_pos(1),_read_pos(0){
}

XRingBuffer::~XRingBuffer(){
    delete [] _buffer;
}

bool XRingBuffer::pushData(const void* data, const DWORD size){
    const DWORD freeSize = getFreeSize();
    if(freeSize < size)
    {
        return false;
    }
    const DWORD readPos =_read_pos;
    const DWORD writePos = _write_pos;
    if(writePos > readPos)
    {
        const DWORD lenFromWritePosToBufferEnd = _size - writePos;
        if(size <= lenFromWritePosToBufferEnd)
        {
            memcpy(_buffer + _write_pos, data, size);
            _write_pos += size;
            if(_write_pos == _size)
            {
                _write_pos = 0;
            }
            else if(_write_pos > _size)
            {
                std::cout << "wirtepos cannot bigger than size\n";
                return false;
            }

            return true;
        }
        else
        {   // 先拷贝前一部分到缓冲区尾部
            memcpy(_buffer + _write_pos, data, lenFromWritePosToBufferEnd);
            const DWORD secondPartLen = size - lenFromWritePosToBufferEnd;
            // 拷贝后一部分到缓冲区前部
            memcpy(_buffer, ((char*)data) + lenFromWritePosToBufferEnd, secondPartLen);
            _write_pos = secondPartLen;
            return true;
        }
    }
    else if(writePos < readPos)
    {
        memcpy(_buffer + writePos, data, size);
        _write_pos += size;
        return true;
    }
    else
    {
        std::cout << "write pos equal read pos, it's an error\n";
        return false;
    }
}

bool XRingBuffer::copyData(void* dest, const DWORD destSize, const DWORD copySize){
    return copyDataWithAddReadPosOption(dest, destSize, copySize, false);
}

bool XRingBuffer::popData(void* dest, const DWORD destSize, const DWORD popSize){
    return copyDataWithAddReadPosOption(dest, destSize, popSize, true);
}

bool XRingBuffer::popData(const DWORD popSize){
    return copyDataWithAddReadPosOption(nullptr, 0, popSize, true);
}

const DWORD XRingBuffer::getUsedSize() const{
    const DWORD writePos = _write_pos;
    const DWORD readPos = _read_pos;
    if(writePos > readPos)
    {
        return writePos - readPos - 1;
    }
    else if(writePos < readPos)
    {
        return (_size - readPos - 1) + _write_pos;
    }
    else
    {
        std::cout <<"write pos equal read pos, it's an error\n";
        return 0;
    }
}

const DWORD XRingBuffer::getFreeSize() const{
    const DWORD usedSize = getUsedSize();
    return _size - (usedSize + XRING_BUFFER_READ_POS_AND_WRITE_POS_SIZE);
}

bool XRingBuffer::copyDataWithAddReadPosOption(void* dest, const DWORD destSize,
                                               const DWORD copySize, bool addReadPos){
    const DWORD usedSize = getUsedSize();
    if(usedSize < copySize)
    {
        return false;
    }

    if(dest != nullptr)
    {
        if(destSize < copySize)
        {
            std::cout << "dest buffer size is smaller than copy size\n";
            return false;
        }
    }
    const DWORD writePos = _write_pos;
    const DWORD readPos = _read_pos;
    if(writePos > readPos)
    {
        if(dest != nullptr)
        {
            memcpy(dest, _buffer + readPos + 1, copySize);
        }
        if(addReadPos)
        {
            _read_pos += copySize;
        }
        return true;
    }
    else if(writePos < readPos)
    {
        const DWORD lenFromReadPosToBufferEnd = _size - readPos - 1;
        if(copySize <= lenFromReadPosToBufferEnd)
        {
            if(dest != nullptr)
            {
                memcpy(dest, _buffer + readPos + 1, copySize);
            }
            if(addReadPos)
            {
                _read_pos += copySize;
                assert(_read_pos < _size);
            }
            return true;
        }
        else
        {
            const DWORD secondPartLen = copySize - lenFromReadPosToBufferEnd;
            if(dest != nullptr)
            {
                memcpy(dest, _buffer + readPos + 1, lenFromReadPosToBufferEnd);
                memcpy(((char*)dest) + lenFromReadPosToBufferEnd, _buffer, secondPartLen);
            }
            if(addReadPos)
            {
                _read_pos = secondPartLen - 1;
            }
            return true;
        }
    }
    else
    {
        std::cout << "write pos equal read pos, it's an error\n";
        return false;
    }
}
