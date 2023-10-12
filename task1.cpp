#include "iostream"
#include "vector"
#include "random"
#include "numeric"
#include "algorithm"
#include "iomanip"



// a function to create vector of randomly generated numbers
std::vector<double> random_generator(int n, int s, double p, unsigned int k){
   std::vector<double> random_numbers;
    std::mt19937_64 generator(s);
    //generator.seed(s);
    std::negative_binomial_distribution<int> dist(k, p);
    int rand = 0; // random number
    for (int i = 0; i < n; i++) {
        rand = dist(generator);
        random_numbers.push_back(rand);
    }
    return random_numbers;
}

// a function of computing mean of a vector
double mean_calculator(std::vector<double> v){
    double mean = std::accumulate(v.begin(), v.end(), 0.0) / v.size();
    return mean;
}

// a function to calculate standard deviation
double sd_calculator (std::vector<double> v, double mean){
    double accum = 0;
    int n = v.size();
    for (int i = 0; i < n; i++){
        accum += pow((v[i] - mean), 2);
    }
    return sqrt(accum / (n - 1));
}

// a function to calculate scaling
std::vector <double> scale_calculator (std::vector<double> v){
    std::vector <double> scaled_v;
    for (auto num : v){
        scaled_v.push_back( log2(abs(num) + 1) );
    }
    //std::sort(std::begin(scaled_v), std::end(scaled_v), std::greater<>());
    return scaled_v;
}

// a function to calculate t-test
double t_value (int n, int m, double v1_sd, double v2_sd, double v1_mean, double v2_mean) {
    double v1_variance = pow(v1_sd, 2);
    double v2_variance = pow(v2_sd, 2);
//pooled standard deviation
    double sp = sqrt(((n - 1 ) * v1_variance + (m - 1) * v2_variance) / (n + m - 2));
//t_test
    double t = (v1_mean - v2_mean) / (sp * sqrt(1.0 / n + 1.0 / m));
    return t;
}

// a function to shuffle
std::vector <double> shuffle (int n, int s, std::vector<double> v){
    std::vector <double> num_seq(n); // to store the sequence of numbers
    std::vector <double> multiplied;
    std::iota (num_seq.begin(), num_seq.end(), 1);
    std::shuffle(num_seq.begin(), num_seq.end(), std::mt19937_64(s));
    for(size_t i=0; i < n; i++){
        multiplied.push_back(v[i] * num_seq[i]);
    }
    return multiplied;
}

// a function to sort
std::vector <double> sorter (std::vector <double> v){
    std::vector <double> odd; // to store the numbers which their nearest int is even
    std::vector <double> even; // to store the numbers which their nearest int is odd

    for (auto el : v) {
        if (int(round(el)) % 2 == 0) {
            even.push_back(el);
        } else {
            odd.push_back(el);
        }
    }

    // sorting in descending way
    std::sort(std::begin(even), std::end(even), std::greater<>());

    // sorting in ascending way
    std::sort(std::begin(odd), std::end(odd));

    // merging two sorted vectors
    std::vector <double> sorted_v = even;
    sorted_v.insert(sorted_v.end(), odd.begin(), odd.end());

    return sorted_v;
}

int main(int argc, const char* argv[]) {
    if (argc != 6){
        std::cout << "wrong number of inputs" << std::endl;
    }

    // input parameters
    int n = std::stoi(argv[1]);
    int m = std::stoi(argv[2]);
    unsigned int s = std::stoul((argv[3]));
    double p = std::stod(argv[4]);
    unsigned int k = std::stoul(argv[5]);

    // 1st randomly generated vector (v1)
    const std::vector<double> v1 = random_generator(n, s, p, k);

    // mean of v1
    const double mean_v1 = mean_calculator (v1);

    // scaled v1
    std::vector<double> scaled_v1_unsorted =  scale_calculator(v1); //unsorted scaled v1 to be used in shuffle
    std::vector<double> scaled_v1 =  scale_calculator(v1);
    std::sort(std::begin(scaled_v1), std::end(scaled_v1), std::greater<>()); // sorted scaled v1

    // standard deviation of v1 (sd_v1)
    double sd_v1 = sd_calculator(v1, mean_v1);

    std::cout << std::setprecision(3) << "V1 Mean: " << mean_v1 << std::endl;
    std::cout << std::setprecision(3) << "V1 Sample standard deviation: " << sd_v1 << std::endl;


    if (n < 11) {
        std::cout << "V1 Top " << n << " elements: ";
        for (int i = 0; i < scaled_v1.size(); i++) {
            std::cout <<  std::setprecision(3) << scaled_v1[i];
            if (i != (scaled_v1.size() - 1)) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    } else {
        std::cout << "V1 Top 10 elements: ";
        for (int i = 0; i < 10; i++) {
            std::cout <<  std::setprecision(3) << scaled_v1[i];
            if (i != 9) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    }

    // 2nd randomly generated vector (v2)
    const std::vector<double> v2 = random_generator(m, (2 * s), p, k);

    // mean of v2
    const double mean_v2 = mean_calculator (v2);

    // scaled v2
    std::vector<double> scaled_v2 =  scale_calculator(v2);
    std::sort(std::begin(scaled_v2), std::end(scaled_v2), std::greater<>());

    // standard deviation of v2 (v2_sd)
    double sd_v2 = sd_calculator(v2, mean_v2);

    std::cout << std::setprecision(3) << "V2 Mean: " << mean_v2 << std::endl;
    std::cout << std::setprecision(3) << "V2 Sample standard deviation: " << sd_v2  << std::endl;

    if (m < 11) {
        std::cout << "V2 Top " << m << " elements: ";
        for (int i = 0; i < scaled_v2.size(); i++) {
            std::cout << std::setprecision(3) << scaled_v2[i];
            if (i != (scaled_v2.size() - 1)) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    } else {
        std::cout << "V2 Top 10 elements: ";
        for (int i = 0; i < 10; i++) {
            std::cout <<  std::setprecision(3) << scaled_v2[i];
            if (i != 9) {
                std::cout << ", ";
            } else {
                std::cout << std::endl;
            }
        }
    }
    std::cout << std::endl;

    std::cout << "Comparing V1 and V2..." << std::endl;
    std::cout << "Unscaled t-statistic: " << t_value(n , m, sd_v1, sd_v2, mean_v1, mean_v2) << std::endl;

    double scaled_mean1 = mean_calculator(scaled_v1);
    double scaled_mean2 = mean_calculator(scaled_v2);
    double scaled_sd1 = sd_calculator(scaled_v1, scaled_mean1);
    double scaled_sd2 = sd_calculator(scaled_v2, scaled_mean2);
    std::cout << "Comparing log2 scaled V1 and V2..." << std::endl;
    std::cout << "Scaled t-statistic: " << t_value(n, m,
                                                   scaled_sd1, scaled_sd2,
                                                   scaled_mean1, scaled_mean2) << std::endl;
    std::cout << "Total degrees of freedom: " << (v1.size() + v2.size() - 2) << std::endl;
    std::cout << std::endl;

    std::vector<double> shuffled_v =  shuffle(n, (s * 7), scaled_v1_unsorted);

    const std::vector<double> sorted_v = sorter(shuffled_v);


    std::cout << "Sorted vector: ";
    for (int i = 0; i < sorted_v.size(); i++) {
        std::cout << sorted_v[i];
        if (i != (sorted_v.size() - 1)) {
            std::cout << ", ";
        } else {
            std::cout << std::endl;
        }
    }
  return 0;
}
