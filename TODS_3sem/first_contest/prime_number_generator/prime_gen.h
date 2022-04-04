bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

class PrimeNumberGenerator {
 public:
    explicit PrimeNumberGenerator(int start) {
        current_number = start;
        while (!isPrime(current_number)) {
            current_number = GetNextPrime();
        }
        start_is_prime = true;
    }
    int GetNextPrime() {
        if (start_is_prime) {
            start_is_prime = false;
            return current_number;
        }

        if (current_number <= 1) {
            current_number = 2;
            return current_number;
        }

        bool prime_is_founded = false;

        while (!prime_is_founded) {
            current_number++;
            if (isPrime(current_number)) {
                prime_is_founded = true;
            }
        }
        return current_number;
    }

 private:
    int current_number;
    bool start_is_prime;
};
