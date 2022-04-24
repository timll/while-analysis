A bit of the while language combined with java-style.
```
Program -> (Stmt;)+

CompoundStmt -> { (Stmt;)* } 

Stmt -> Var = Expr |
        skip |
        if (Expr) CompoundStmt [else CompoundStmt] |
        while (Expr) CompoundStmt

Expr -> Number |
        Var |
        Expr Binop Expr |
        Unop Expr

Binop -> ABinop | RBinop

ABinop -> + | - | * | /

RBinop -> < | <= | == | != | => | >

Unop -> - | !
```