#include "Service.hpp"
#include "API.hpp"

int main() {
    Service service;
    API api(service);
    api.run();
    return 0;
}
