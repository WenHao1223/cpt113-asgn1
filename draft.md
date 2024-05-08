**BakeryItem**
protected:
- name
- description
- price
- quantity
- **Ingredient**[] ingredientUsed // composition

---

**Ingredient** // for describing ingredients used in BakeryItem and ingredients left in inventory
private:
- name
- description
- piece (from **Cookie**)
- weight (from **Cake**) // in gram
public:
- makeBakeryItem()
  = deduct **Ingredient** from inventoryItem

// one of the examples of ingredient used in tiramisu
{
  name: "Flour",
  description: "Main ingredient of cake",
  piece: 0,
  weight: 500
}

---

**Cookie**
- Cookie : public BakeryItem
- friend calculatePrice(piece)
  = price * piece

---

**Cake**
- Cake :: public BakeryItem
- friend calculatePrice(weight)
  = price * weight

---

**User**
protected:
- id // employeeID if from **Employee**, memberID if from **Members**
- name
- identityNumber

---

**Employee**
- Employee : private User

---

**Members**

---

void calculatePrice()