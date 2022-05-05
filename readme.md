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

Expr -> Boolean |
        Number |
        Var |
        Expr Binop Expr |
        Unop Expr

Boolean -> true | false

Binop -> ABinop | CBinop

ABinop -> + | - | * | /

CBinop -> < | <= | == | != | => | >

Unop -> - | !
```