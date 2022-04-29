A bit of the while language combined with java-style.
```
Program -> (Stmt;)+

CompoundStmt -> { (Stmt;)* } 

Stmt -> Type Var = Expr |
        Var = Expr |
        skip |
        if (Expr) CompoundStmt [else CompoundStmt] |
        while (Expr) CompoundStmt

Type -> int | bool

Expr -> Number |
        Var |
        Expr Binop Expr |
        Unop Expr

Binop -> ABinop | CBinop

ABinop -> + | - | * | /

CBinop -> < | <= | == | != | => | >

Unop -> - | !
```