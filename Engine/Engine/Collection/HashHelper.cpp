#include "Engine/Collection/HashHelper.h"
#include "Engine/System/Exception.h"
#include "Engine/Math/Math.h"
namespace Engine {
	const int32 HashHelper::primes[] = {
		3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919,
		1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591, 17519,
		21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437, 187751, 225307,
		270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263, 1674319, 2009191,
		2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369
	};
	const int32 HashHelper::hashPrime = 101;
	bool HashHelper::IsPrime(int32 value) {
		if ((value & 1) == 0) {
			return value == 2;
		}
		int32 limit = (int32)Math::Sqrt(value);
		for (int32 divisor = 3; divisor <= limit; divisor += 2) {
			if ((value % divisor) == 0) {
				return false;
			}
		}
		return true;
	}
	int32 HashHelper::GetPrime(int32 min) {
		if (min < 0) {
			throw ArgumentOutOfRangeException("min", "Cannot be smaller than 0.");
		}
		// Find in the pre-defined.
		for (int32 prime : primes) {
			if (prime >= min) {
				return prime;
			}
		}
		// If not pre-defined, calculate it.
		for (int32 i = (min | 1); i < 2147483647; i += 2) {
			if (IsPrime(i) && ((i - 1) % hashPrime != 0)) {
				return i;
			}
		}
		return min;
	}
}