#pragma once
#include "common.h"

/* A looser bucket hashmap implementation with O(ln(n)) search times */

typedef struct hashentry {
	uint64 key;
	uint32 hash;
	void * data;

} hashentry;

typedef struct hashbucket {
	hashentry * data;
	int size;
	hashbucket * left;
	hashbucket * right;
	uint32 mask;
	int bsize;
	hashbucket(int bucket_size) {
		bsize = bucket_size;
		left = right = NULL;
		data = new hashentry[bucket_size];
		size = 0;
		mask = 1;
	}

	hashbucket * split(uint64 key) {
		uint32 new_mask = mask << 1;

		left = new hashbucket(bsize);
		left->mask = new_mask;
		right = new hashbucket(bsize);
		right->mask = new_mask;

		int i;
		for (i = 0; i < size; i++) {
			if (data[i].hash & mask) {
				right->data[right->size++] = data[i];
			}
			else {
				left->data[left->size++] = data[i];
			}
		}
		delete[] data;

		if (key & mask) {
			return right;
		}
		else {
			return left;
		}
	}
} hashbucket;

uint32 hash_fn(uint64 key);

typedef struct hashmap {
	int size;
	hashbucket * buckets_root;
	int bucket_size;

	int(*cmp_fn)(void * a, void * b);

	hashmap(int ibucket_size) {
		bucket_size = ibucket_size;
		buckets_root = new hashbucket(bucket_size);
		size = 0;
		cmp_fn = 0;
	}

	hashbucket * search_bucket(uint64 key, uint32 hash) {
		uint32 mask = 1;
		hashbucket * b = buckets_root;
		printf("%X\n", b->size);
		while (b) {
			if (!b->right) {
				return b;
			}
			else {
				uint64 side = hash & mask;
				if (side) {
					b = b->right;
				}
				else {
					b = b->left;
				}
				mask = b->mask;
			}
		}
		printf("hash error\n");
		exit(0);
	}

	void put(uint64 key, void * data) {
		uint32 hash = hash_fn(key);
		if (hash == 0) hash = 1;
		printf("put %X\n", hash);
		hashbucket * b = search_bucket(key, hash);
		printf("b %X\n", b);
		int i;
		hashentry e;
		e.data = data;
		e.key = key;
		e.hash = hash;
		for (i = 0; i < b->size; i++) {
			if (b->data[i].hash == 0) {
				b->data[i] = e;
				return;
			}
			if (b->data[i].hash == hash) {
				if (b->data[i].key == key && (!cmp_fn || cmp_fn(&b->data[i].key, &key))) {
					b->data[i] = e;
					return;
				}
			}
		}

		while (b->size == bucket_size) {
			b = b->split(key);
		}
		
		b->data[b->size++] = e;
		printf("put in %X\n", b->mask);
		size++;
	}

	void * get(uint64 key) {
		int i;
		uint32 hash = hash_fn(key);
		if (hash == 0) hash = 1;
		hashbucket * b = search_bucket(key, hash);
		for (i = 0; i < b->size; i++) {
			if (b->data[i].hash == hash) {
				if (b->data[i].key == key && (!cmp_fn || cmp_fn(&b->data[i].key, &key))) {
					return b->data[i].data;
				}
			}
		}
		return NULL;
	}

} hashmap;
