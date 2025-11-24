# Stock Management System

## Introduction

The Stock Management System is a console-based application developed in C to streamline inventory operations for small businesses and academic purposes. The system allows users to maintain records of products efficiently, focusing on reliability and ease of use.

## Purpose

This project demonstrates core C programming concepts—including structures, file handling, and modular design—while addressing a real-world need: systematic and error-free management of inventory stock.

## Features

### Add Product

Allows the user to enter all details of a new product (ID, name, company, price, quantity) and saves it to the data file. Duplicate IDs are checked to ensure accuracy.

### View Products

Displays a list of all products in a tabular format, enabling users to review current inventory at any time.

### Search Product

Supports quick lookup by product ID, letting users find item details instantly and reducing time spent searching records.

### Update Product

Gives users the ability to modify existing product information (company, price, quantity) as inventory changes occur.

### Delete Product

Removes unwanted or outdated products from inventory, helping keep records up to date. Confirmation is requested before deletion.

## Programming Requirements

- ANSI C standard
- Use of structs and arrays for data storage
- File operations (`fopen`, `fread`, `fwrite`) to ensure info persists after program exits
- Modularized code for each operation (add, view, search, update, delete)
- Does not require external libraries

## How To Use

1. Compile the program:
    ```bash
    gcc stock_management_system.c -o stock_management_system
    ```
2. Run it in the terminal:
    ```bash
    ./stock_management_system
    ```
3. Use the on-screen menu to add, view, update, search, or delete products.

## Menu Sample

```
==== Stock Management System ====
1. Add Product
2. View Products
3. Search Product
4. Update Product
5. Delete Product
6. Exit
Enter your choice:
```

## Conclusion

This application illustrates the blending of programming theory with practical use, helping students grasp file handling, struct management, and user interface design in a beginner-friendly project.

## Author

*Your Name*  
ITP Project  
SAI University, Chennai

---

## 💡 Tips for Pasting on GitHub

1. **Copy this entire text** (including the title and all sections)
2. **Go to your GitHub repository** and click on "Add file" → "Create new file"
3. **Name your file:** `README.md` (exactly like this, case-sensitive)
4. **Paste the copied content** into the file editor
5. **Preview tab:** Click the "Preview" button to see how it will look
6. **Commit:** Scroll down and click "Commit new file"

### Formatting Tips

- Keep blank lines between sections for proper spacing
- Don't add extra indentation—GitHub Markdown handles it automatically
- Code blocks use triple backticks (\`\`\`) with the language name
- Headings use `#` symbols (more `#` = smaller heading)
- Lists automatically format with proper bullets

### Common Issues to Avoid

❌ Don't copy from Word/Google Docs (use plain text)  
❌ Don't add extra spaces before lines  
❌ Don't mix tabs and spaces  
✅ Copy directly from here and paste into GitHub  
✅ Use the Preview tab to check formatting before committing

Your README will look clean, professional, and exactly like other academic project repositories!