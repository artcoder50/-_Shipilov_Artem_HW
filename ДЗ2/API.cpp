#include "API.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Errors.hpp"

int parseInt(const std::string& s) {
  try {
    size_t pos = 0;
    int v = std::stoi(s, &pos);
    if (pos != s.size()) throw std::invalid_argument("trailing");
    return v;
  } catch (...) {
    throw ParseError("invalid integer: " + s);
  }
}

double parseDouble(const std::string& s) {
  try {
    size_t pos = 0;
    double v = std::stod(s, &pos);
    if (pos != s.size()) throw std::invalid_argument("trailing");
    return v;
  } catch (...) {
    throw ParseError("invalid double: " + s);
  }
}

void API::buildMethods() {
  methods_["add"] = [this](std::vector<std::string>& t) {
    if (t.size() < 2) {
      throw ParseError("usage: add <type> ...");
    }

    const std::string& type = t[1];

    if (type == "scooter") {
      if (t.size() != 6) {
        throw ParseError("usage: add scooter id name energy score");
      }
      service_.addScooter(t[2], t[3], t[3], parseDouble(t[4]), parseInt(t[5]));
    } else if (type == "bike") {
      if (t.size() != 5) {
        throw ParseError("usage: add bike id name score");
      }
      service_.addBike(t[2], t[3], t[3], parseInt(t[4]));
    } else if (type == "ebike") {
      if (t.size() != 6) {
        throw ParseError("usage: add ebike id name energy score");
      }
      service_.addEbike(t[2], t[3], t[3], parseDouble(t[4]), parseInt(t[5]));
    } else if (type == "helmet") {
      if (t.size() != 4) {
        throw ParseError("usage: add helmet id name");
      }
      service_.addHelmet(t[2], t[3]);
    } else if (type == "dock") {
      if (t.size() != 5) {
        throw ParseError("usage: add dock id name energy");
      }
      service_.addDock(t[2], t[3], parseDouble(t[4]));
    } else {
      throw ParseError("unknown add type: " + type);
    }
  };

  methods_["energy"] = [this](std::vector<std::string>& t) {
    if (t.size() != 1) {
      throw ParseError("usage: energy");
    }
    std::cout << std::fixed << std::setprecision(1) << service_.totalEnergy()
              << '\n';
  };

  methods_["novice"] = [this](std::vector<std::string>& t) {
    if (t.size() != 1) {
      throw ParseError("usage: novice");
    }
    auto list = service_.noviceList();
    for (auto* v : list) {
      std::cout << v->inventoryId() << " " << v->name() << '\n';
    }
  };

  methods_["list"] = [this](std::vector<std::string>& t) {
    if (t.size() != 1) {
      throw ParseError("usage: list");
    }
    service_.printAll(std::cout);
  };

  methods_["focus"] = [this](std::vector<std::string>& t) {
    if (t.size() != 2) {
      throw ParseError("usage: focus id");
    }
    service_.focus(t[1]);
  };

  methods_["show_focus"] = [this](std::vector<std::string>& t) {
    if (t.size() != 1) {
      throw ParseError("usage: show_focus");
    }
    std::cout << service_.showFocus() << '\n';
  };

  methods_["remove"] = [this](std::vector<std::string>& t) {
    if (t.size() != 2) {
      throw ParseError("usage: remove id");
    }
    service_.remove(t[1]);
  };

  methods_["models"] = [this](std::vector<std::string>& t) {
    if (t.size() != 1) {
      throw ParseError("usage: models");
    }
    service_.printModels(std::cout);
  };

  methods_["max"] = [this](std::vector<std::string>& t) {
    if (t.size() != 2) {
      throw ParseError("usage: max <scooter|ebike|dock>");
    }

    const std::string& type = t[1];
    std::cout << std::fixed << std::setprecision(1);

    if (type == "scooter") {
      auto* s = service_.mostPoverfulScooter();
      if (!s) throw NotFoundError("no such devices");
      std::cout << s->inventoryId() << " " << s->name() << " "
                << s->dailyEnergy() << '\n';
    } else if (type == "ebike") {
      auto* e = service_.mostPoverfulEbike();
      if (!e) throw NotFoundError("no such devices");
      std::cout << e->inventoryId() << " " << e->name() << " "
                << e->dailyEnergy() << '\n';
    } else if (type == "dock") {
      auto* d = service_.mostPoverfulDock();
      if (!d) throw NotFoundError("no such devices");
      std::cout << d->inventoryId() << " " << d->name() << " "
                << d->dailyEnergy() << '\n';
    } else {
      throw ParseError("unknown max type: " + type);
    }
  };

  methods_["quit"] = [this](std::vector<std::string>& t) {
    if (t.size() != 1) {
      throw ParseError("usage: quit");
    }
    running_ = false;
  };
}

void API::readCommand() {
  std::string line;
  if (!std::getline(std::cin, line)) {
    running_ = false;
    return;
  }

  std::istringstream iss(line);
  std::vector<std::string> tokens;
  std::string tok;
  while (iss >> tok) {
    tokens.push_back(tok);
  }

  if (tokens.empty()) {
    return;
  }

  auto it = methods_.find(tokens[0]);
  if (it == methods_.end()) {
    throw ParseError("unknown command: " + tokens[0]);
  }
  it->second(tokens);
}

void API::printError(const std::string& msg) {
  std::cout << "error: " << msg << '\n';
}

void API::run() {
  while (running_) {
    try {
      readCommand();
    } catch (const std::exception& e) {
      printError(e.what());
    }
  }
}
