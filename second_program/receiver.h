class Receiver {
public:
    Receiver();
    void receive();
    void analyze();
    void print();
private:
    int _received_sum;
};