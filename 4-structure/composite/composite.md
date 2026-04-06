using Currency = double;

class Equipment {
public: 
    virtual ~Equipment();

    virtual Currency NetPrice() = 0; 

 
    virtual void Add(Equipment*) {}
    virtual void Remove(Equipment*) {}

protected: 
    Equipment(); 
};

class FloppyDisk : public Equipment { 
public: 
    FloppyDisk(); 
    virtual Currency NetPrice() override { return 0.50; } 
};

class CompositeEquipment : public Equipment { 
public:
    ~CompositeEquipment() {
        for (auto e: _equipment)
            delete e;
    }

    virtual Currency NetPrice() {
        Currency price = 0;
        for (auto e: _equipment)
            price += e->NetPrice();
        return price;
    }
 
    void Add(Equipment* equipment) override {
        _equipment.push_back(equipment);
    }
    
    void Remove(Equipment* equipment) override {
        auto it = std::find(_equipment.begin(), _equipment.end(), equipment);
        if (it != _equipment.end()) {
            _equipment.erase(it);
        }
    }

protected: 
    CompositeEquipment(); 
private: 
    std::vector<Equipment*> _equipment; 
};

using Watt = double;

class Computer : public CompositeEquipment {
public:
    Watt GetTotalPowerConsumption() const {
        return 500.0;
    }
};
