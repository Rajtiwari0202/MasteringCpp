#pragma once
#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>
#include <new>

namespace CoreEngine {

    /**
     * @brief High-Performance Arena / Linear Bump Allocator
     * Zero fragmentation, O(1) allocation, O(1) bulk deallocation.
     */
    class ArenaBumpAllocator {
    private:
        uint8_t* m_buffer;
        size_t m_capacity;
        size_t m_offset;

    public:
        explicit ArenaBumpAllocator(size_t capacityBytes)
            : m_capacity(capacityBytes), m_offset(0) {
            m_buffer = static_cast<uint8_t*>(::operator new(capacityBytes));
        }

        ~ArenaBumpAllocator() {
            ::operator delete(m_buffer);
        }

        ArenaBumpAllocator(const ArenaBumpAllocator&) = delete;
        ArenaBumpAllocator& operator=(const ArenaBumpAllocator&) = delete;

        void* allocate(size_t bytes, size_t alignment = alignof(std::max_align_t)) {
            uintptr_t currentAddr = reinterpret_cast<uintptr_t>(m_buffer + m_offset);
            size_t padding = (alignment - (currentAddr % alignment)) % alignment;

            if (m_offset + padding + bytes > m_capacity) {
                throw std::bad_alloc(); // Arena exhausted
            }

            m_offset += padding;
            void* ptr = m_buffer + m_offset;
            m_offset += bytes;
            return ptr;
        }

        template <typename T, typename... Args>
        T* create(Args&&... args) {
            void* mem = allocate(sizeof(T), alignof(T));
            return new (mem) T(std::forward<Args>(args)...);
        }

        void reset() noexcept {
            m_offset = 0; // O(1) bulk reset
        }

        size_t bytesUsed() const noexcept { return m_offset; }
        size_t capacity() const noexcept { return m_capacity; }
    };

    /**
     * @brief High-Performance Fixed-Size Block Pool Allocator
     * O(1) allocation and O(1) individual block deallocation via Free-List.
     */
    template <typename T, size_t BlockCount>
    class FixedPoolAllocator {
    private:
        union Node {
            Node* nextFree;
            alignas(T) uint8_t storage[sizeof(T)];
        };

        Node* m_pool;
        Node* m_freeList;

    public:
        FixedPoolAllocator() {
            m_pool = static_cast<Node*>(::operator new(sizeof(Node) * BlockCount));
            m_freeList = &m_pool[0];

            for (size_t i = 0; i < BlockCount - 1; ++i) {
                m_pool[i].nextFree = &m_pool[i + 1];
            }
            m_pool[BlockCount - 1].nextFree = nullptr;
        }

        ~FixedPoolAllocator() {
            ::operator delete(m_pool);
        }

        FixedPoolAllocator(const FixedPoolAllocator&) = delete;
        FixedPoolAllocator& operator=(const FixedPoolAllocator&) = delete;

        template <typename... Args>
        T* allocate(Args&&... args) {
            if (!m_freeList) {
                throw std::bad_alloc(); // Pool exhausted
            }

            Node* node = m_freeList;
            m_freeList = m_freeList->nextFree;

            T* objectPtr = reinterpret_cast<T*>(node->storage);
            return new (objectPtr) T(std::forward<Args>(args)...);
        }

        void deallocate(T* ptr) noexcept {
            if (!ptr) return;

            ptr->~T(); // Explicit destructor invocation

            Node* node = reinterpret_cast<Node*>(ptr);
            node->nextFree = m_freeList;
            m_freeList = node;
        }
    };
}
