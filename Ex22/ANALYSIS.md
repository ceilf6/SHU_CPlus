# Ex22 和 Ex22b 代码分析

## 概述

这两个目录包含了 SET 纸牌游戏的不同实现版本：

- **Ex22**: 我刚刚完成的基础实现（根据题目要求）
- **Ex22b**: 包含两个高级版本的实现（可能是老师提供的参考代码）

---

## Ex22 - 基础实现版本

### 特点

1. **简洁清晰的类设计**
   - 直接实现所有要求的类和功能
   - 使用标准的 C++ 异常处理 (`std::runtime_error`)
   - 没有使用 namespace

2. **核心类实现**
   - `Carte`: 基础卡片类，包含4个枚举属性
   - `Jeu`: 管理81张卡片（组合关系）
   - `Pioche`: 牌堆，随机抽牌
   - `Plateau`: 桌面，动态数组管理
   - `Combinaison`: 3张卡的组合，判断是否为SET
   - `Controleur`: 游戏控制器

3. **关系设计**
   - **组合（Composition）**: `Jeu` 拥有 `Carte`，`Controleur` 拥有 `Pioche`
   - **聚合（Aggregation）**: `Pioche`, `Plateau`, `Combinaison` 只持有 `Carte*` 指针

4. **优点**
   - 代码结构清晰，易于理解
   - 完整实现了所有题目要求
   - 包含详细的测试用例
   - 注释丰富（中文）

5. **测试覆盖**
   - 枚举类型测试
   - 所有类的基本功能测试
   - SET判断算法测试
   - 游戏流程测试

---

## Ex22b - 高级参考实现

### 版本1: set(1).h / set(1).cpp / main(1).cpp

#### 新增特性

1. **使用 namespace Set**
   - 所有类都封装在 `Set` namespace 中
   - 避免命名冲突

2. **Jeu 类改进**
   - **Singleton 模式**: `static Jeu& getInstance()`
   - 只能有一个游戏实例，全局访问点
   
3. **迭代器模式（Iterator Pattern）**
   - `Iterator`: 基础迭代器（索引based）
   - `const_iterator`: 标准库风格的常量迭代器，支持 range-based for 循环
   - `IteratorForme`: 按形状过滤的迭代器
   - `IteratorBis`: 基于指针的迭代器

4. **迭代器设计模式对比**

```cpp
// Iterator: 基于索引
class Iterator {
    Jeu& instance;
    size_t i;
public:
    const Carte& currentItem();
    bool isDone() const;
    void next();
};

// const_iterator: 支持范围循环
class const_iterator {
    const Jeu& instance;
    size_t i;
public:
    const Carte& operator*();
    bool operator!=(const_iterator other) const;
    void operator++();
};

// IteratorForme: 条件迭代
class IteratorForme {
    Forme forme;
    Jeu& instance;
    size_t i;
public:
    void next() {
        i++;
        while (!isDone() && 
               instance.getCarte(i).getForme() != forme) i++;
    }
};
```

5. **使用示例**

```cpp
Jeu& j = Jeu::getInstance();

// 传统迭代器
Jeu::Iterator it = j.first();
while (!it.isDone()) {
    cout << it.currentItem();
    it.next();
}

// Range-based for
for (auto& c : j) {
    cout << c << "\n";
}
```

---

### 版本2: set(2).h / set(2).cpp / main(2).cpp

#### 核心改进

1. **Carte 类访问控制增强**
   - 构造函数变为 `private`
   - 只有 `Jeu` 类可以创建 `Carte`（friend class）
   - **强制执行组合关系**: 卡片必须由游戏创建

```cpp
class Carte {
private:
    // 构造函数私有化
    Carte(Couleur c, Nombre n, Forme f, Remplissage r);
    friend class Jeu; // 只有Jeu可以创建Carte
public:
    // 只提供getter
    Couleur getCouleur() const;
    // ...
};
```

2. **Jeu 类的多种迭代器**
   - `Iterator`: 基于指针的迭代器
   - `IteratorBis`: 基于索引的迭代器
   - `const_iterator`: 标准库风格
   - `FormeIterator`: 按形状过滤

3. **Pioche 和 Plateau 的完整实现**
   - 拷贝构造和赋值运算符的正确实现
   - 深拷贝管理

4. **Controleur 改进**
   - 使用 Jeu 的 singleton 引用
   - 更清晰的生命周期管理

```cpp
class Controleur {
    Jeu& jeu; // 引用singleton
    Plateau plateau;
    Pioche* pioche;
public:
    Controleur() : jeu(Jeu::getInstance()) {
        pioche = new Pioche(jeu);
    }
    ~Controleur() { delete pioche; }
};
```

---

## 关键设计模式对比

### 1. Singleton 模式

| Ex22 | Ex22b |
|------|-------|
| 允许多个Jeu实例 | 单例模式，全局唯一 |
| `Jeu jeu;` | `Jeu& j = Jeu::getInstance();` |

### 2. 迭代器模式

| Ex22 | Ex22b |
|------|-------|
| 无迭代器 | 多种迭代器实现 |
| 直接访问 `getCarte(i)` | 支持 range-based for 循环 |
| - | 支持条件过滤迭代（按形状） |

### 3. 访问控制

| Ex22 | Ex22b (版本2) |
|------|---------------|
| Carte可以自由创建 | Carte构造函数私有 |
| 任何代码都可以创建Carte | 只有Jeu能创建Carte |
| 弱组合关系 | 强制组合关系 |

---

## 关联关系分析

### Ex22 实现

```
Controleur (Composition)
├── Jeu (Composition)
│   └── Carte[81] (owns, creates, destroys)
├── Plateau (Composition)
│   └── Carte* (Aggregation - doesn't own)
└── Pioche* (Composition)
    └── Carte* (Aggregation - doesn't own)

Combinaison
└── Carte* (Aggregation)
```

### Ex22b 实现

```
Controleur (Composition)
├── Jeu& (Association to Singleton)
│   └── Carte[81] (owns, private constructor)
├── Plateau (Composition with deep copy)
│   └── Carte* (Aggregation)
└── Pioche* (Composition)
    └── Carte* (Aggregation)
```

---

## 技术亮点对比

### Ex22

✅ 实现所有基本功能  
✅ 清晰的代码结构  
✅ 完整的测试覆盖  
✅ 详细的中文注释  
✅ SET判断算法正确  

❌ 缺少迭代器  
❌ 非单例设计  
❌ Carte可以随意创建  

### Ex22b

✅ Singleton模式（全局唯一游戏实例）  
✅ 多种迭代器实现  
✅ 支持 range-based for 循环  
✅ 强制访问控制（Carte私有构造）  
✅ 深拷贝实现（Plateau）  

❌ 代码更复杂  
❌ 学习曲线较陡  

---

## 适用场景

### Ex22 适合：
- 学习基础的类关联关系
- 理解组合 vs 聚合
- 快速原型开发
- 教学示例

### Ex22b 适合：
- 学习设计模式（Singleton, Iterator）
- 理解高级访问控制
- 大型项目的架构参考
- 学习标准库风格的实现

---

## 学习建议

1. **先掌握 Ex22**
   - 理解基本的类关系
   - 掌握指针和动态内存管理
   - 理解组合和聚合的区别

2. **再研究 Ex22b**
   - 学习 Singleton 模式的优缺点
   - 理解迭代器的设计和实现
   - 掌握如何通过访问控制强化设计

3. **实践练习**
   - 在 Ex22 基础上添加迭代器
   - 实现查找 SET 的自动算法
   - 添加多人游戏支持
   - 实现计分系统

---

## 代码质量评估

### Ex22
- **可读性**: ⭐⭐⭐⭐⭐ (5/5)
- **可维护性**: ⭐⭐⭐⭐ (4/5)
- **扩展性**: ⭐⭐⭐ (3/5)
- **性能**: ⭐⭐⭐⭐ (4/5)
- **设计模式**: ⭐⭐ (2/5)

### Ex22b
- **可读性**: ⭐⭐⭐ (3/5)
- **可维护性**: ⭐⭐⭐⭐⭐ (5/5)
- **扩展性**: ⭐⭐⭐⭐⭐ (5/5)
- **性能**: ⭐⭐⭐⭐ (4/5)
- **设计模式**: ⭐⭐⭐⭐⭐ (5/5)

---

## 总结

- **Ex22** 是一个**清晰、直接的实现**，完美地完成了练习要求
- **Ex22b** 展示了**专业级的设计模式应用**，适合进阶学习
- 两者各有优势，取决于项目需求和学习阶段
- 建议从 Ex22 开始学习，逐步过渡到 Ex22b 的高级特性
