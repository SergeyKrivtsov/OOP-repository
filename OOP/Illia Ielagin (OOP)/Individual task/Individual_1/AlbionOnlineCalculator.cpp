#include <iostream>
#include <string>

using namespace std;


#define STANDARD_SALES_TAX 0.08  // Податок на продаж для звичайних гравців
#define PREMIUM_SALES_TAX 0.04   // Податок на продаж для преміум-гравців
#define LISTING_TAX 0.025        // Податок на розміщення замовлень на продаж

// Перелічуваний тип для якості предмета
enum class ItemQuality {
    Normal,
    Good,
    Outstanding,
    Excellent,
    Masterpiece
};

// Структура для зберігання інформації про товар
struct ItemInfo {
    string itemName;       
    int tierLevel;           
    int enchantmentLevel;     
    ItemQuality quality;      

    ItemInfo() {
        itemName = "";
        tierLevel = 0;
        enchantmentLevel = 0;
        quality = ItemQuality::Normal;
    }

    ItemInfo(string name, int tier, int enchant, ItemQuality qual) {
        itemName = name;
        tierLevel = tier;
        enchantmentLevel = enchant;
        quality = qual;
    }

    // Метод для перетворення якості у текст
    static string qualityToString(ItemQuality quality) {
        switch (quality) {
        case ItemQuality::Normal: return "Normal";
        case ItemQuality::Good: return "Good";
        case ItemQuality::Outstanding: return "Outstanding";
        case ItemQuality::Excellent: return "Excellent";
        case ItemQuality::Masterpiece: return "Masterpiece";
        default: return "Unknown";
        }
    }

    // Метод для отримання якості з тексту
    static ItemQuality stringToQuality(const string& qualityStr) {
        if (qualityStr == "Normal") return ItemQuality::Normal;
        if (qualityStr == "Good") return ItemQuality::Good;
        if (qualityStr == "Outstanding") return ItemQuality::Outstanding;
        if (qualityStr == "Excellent") return ItemQuality::Excellent;
        if (qualityStr == "Masterpiece") return ItemQuality::Masterpiece;
        throw invalid_argument("Invalid quality string: " + qualityStr);
    }
};

// Абстрактний клас для угод
class DealSample {
protected:
    ItemInfo itemInfo;    // Інформація про товар
    int quantity;         // Кількість товару
    string description;   // Опис товару або примітка
    string dealName;      // Назва угоди

public:
    DealSample(ItemInfo info, int qty, string desc, string name) {
        itemInfo = info;
        quantity = qty;
        description = desc;
        dealName = name;
    }

    // Геттери для роботи з файлами
    string getDealName() const {
        return dealName;
    }

    virtual void displayInfo() const {
        cout << "Item: " << itemInfo.itemName << " (Tier " << itemInfo.tierLevel << ", Enchantment " << itemInfo.enchantmentLevel << ")\n";
        cout << "Item Quality: " << ItemInfo::qualityToString(itemInfo.quality) << "\n";
        cout << "Quantity: " << quantity << "\n";
        cout << "Description: " << description << "\n";
        cout << "Deal Name: " << dealName << "\n";
    }

    virtual void saveToFile(const string& filename) const = 0;
    virtual void loadFromFile(const string& filename) = 0;

    virtual ~DealSample() = default; 
};

// Клас спадкоємець для угод купівлі-продажу
class BuySellDeal : public DealSample {
private:
    double purchasePricePerUnit; // Ціна за одиницю при покупці
    double salePricePerUnit;     // Ціна за одиницю при продажу
    bool isPremium;              // Статус преміум-гравця
    bool isListedForSale;        // Чи є замовлення продажу (додатковий податок)

public:
    BuySellDeal(ItemInfo info, int qty, double purchasePrice, double salePrice, string desc, string name, bool premiumStatus, bool listedForSale)
        : DealSample(info, qty, desc, name) {
        purchasePricePerUnit = purchasePrice;
        salePricePerUnit = salePrice;
        isPremium = premiumStatus;
        isListedForSale = listedForSale;
    }

    double calculateTaxPerUnit() const {
        double salesTax = isPremium ? PREMIUM_SALES_TAX : STANDARD_SALES_TAX;
        if (isListedForSale) {
            salesTax += LISTING_TAX; // Додаємо 2.5% податок на розміщення
        }
        return salePricePerUnit * salesTax; // Податок на одиницю
    }

    double calculateTotalProfit() const {
        double totalSales = quantity * salePricePerUnit;
        double totalPurchase = quantity * purchasePricePerUnit;
        double totalTax = calculateTaxPerUnit() * quantity;
        return totalSales - totalPurchase - totalTax;       // Чистий прибуток
    }

    void displayInfo() const override {
        DealSample::displayInfo();
        cout << "Purchase Price Per Unit: " << purchasePricePerUnit << "\n";
        cout << "Sale Price Per Unit: " << salePricePerUnit << "\n";
        cout << "Premium Status: " << (isPremium ? "Yes" : "No") << "\n";
        cout << "Listed for Sale: " << (isListedForSale ? "Yes" : "No") << "\n";
        cout << "Tax Per Unit: " << calculateTaxPerUnit() << "\n";
        cout << "Total Profit: " << calculateTotalProfit() << "\n";
    }

    void saveToFile(const string& filename) const override {
        FILE* file;
        fopen_s(&file, filename.c_str(), "w");
        if (!file) {
            cerr << "Error: Could not open file for writing: " << filename << endl;
            return;
        }
        fprintf(file, "%s\n%d\n%d\n%d\n%s\n%s\n%s\n%.2f\n%.2f\n%d\n%d\n",
            itemInfo.itemName.c_str(),
            itemInfo.tierLevel,
            itemInfo.enchantmentLevel,
            quantity,
            description.c_str(),
            dealName.c_str(),
            ItemInfo::qualityToString(itemInfo.quality).c_str(),
            purchasePricePerUnit,
            salePricePerUnit,
            isPremium,
            isListedForSale);
        fclose(file);
    }

    void loadFromFile(const string& filename) override {
        FILE* file;
        fopen_s(&file, filename.c_str(), "r");
        if (!file) {
            cerr << "Error: Could not open file for reading: " << filename << endl;
            return;
        }
        char nameBuffer[100], descBuffer[100], dealNameBuffer[100], qualityBuffer[20];
        if (!(fscanf_s(file, "%99[^\n]\n%d\n%d\n%d\n%99[^\n]\n%99[^\n]\n%19s\n%lf\n%lf\n%d\n%d\n",
            nameBuffer, sizeof(nameBuffer),
            &itemInfo.tierLevel,
            &itemInfo.enchantmentLevel,
            &quantity,
            descBuffer, sizeof(descBuffer),
            dealNameBuffer, sizeof(dealNameBuffer),
            qualityBuffer, sizeof(qualityBuffer),
            &purchasePricePerUnit,
            &salePricePerUnit,
            &isPremium,
            &isListedForSale))) {
            cerr << "Error: Failed to read all data from file: " << filename << endl;
            fclose(file);
            return;
        }
        itemInfo.itemName = nameBuffer;
        description = descBuffer;
        dealName = dealNameBuffer;
        try {
            itemInfo.quality = ItemInfo::stringToQuality(qualityBuffer);
        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
            fclose(file);
            return;
        }
        fclose(file);
    }
};


bool isDealExists(const string& mainFile, const string& dealName) {
    FILE* file;
    fopen_s(&file, mainFile.c_str(), "r");
    if (!file) {
        return false; // Якщо файл не відкрився, вважаємо, що угод немає
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        string trimmedLine = string(line);
        trimmedLine.erase(trimmedLine.find_last_not_of("\n\r") + 1); // Видалення символів переносу
        if (trimmedLine == dealName) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void addDealFile(const string& mainFile, const string& dealFile) {
    if (isDealExists(mainFile, dealFile)) {
        cout << "Error: A deal with the name '" << dealFile << "' already exists!" << endl;
        return;
    }

    FILE* file;
    fopen_s(&file, mainFile.c_str(), "a");
    if (!file) {
        cerr << "Error: Could not open main file: " << mainFile << endl;
        return;
    }
    fprintf(file, "%s\n", dealFile.c_str());
    fclose(file);
}

// Тестування
int main() {
    const string mainFile = "deals.txt";

    // Створення нової угоди
    ItemInfo info("Iron Sword", 4, 2, ItemQuality::Normal);
    BuySellDeal deal(info, 100, 500, 700, "Buy in Martlock, sell in Caerleon", "Black Market Deal", true, false);

    // Збереження угоди у файл
    string dealFile = deal.getDealName() + ".txt";
    if (!isDealExists(mainFile, dealFile)) {
        deal.saveToFile(dealFile);
        addDealFile(mainFile, dealFile);
    }
    else {
        cout << "Deal already exists!" << endl;
    }

    // Завантаження угоди з файлу у новий екземпляр
    BuySellDeal loadedDeal(ItemInfo(), 0, 0, 0, "", "", false, false);
    loadedDeal.loadFromFile(dealFile);
    loadedDeal.displayInfo();

    return 0;
}

