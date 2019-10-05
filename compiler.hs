data Expr = Num Int
     	  | Add Expr Expr
	  | Mult Expr Expr
	  deriving (Eq, Show)

data Instr = PUSH Int
     	   | ADDI
	   | MULTI
	   deriving (Eq, Show)

interp :: Expr -> Int
interp (Num x) = x
interp (Add e1 e2) = interp e1 + interp e2
interp (Mult e1 e2) = interp e1 * interp e2

compile :: Expr -> [Instr]
compile (Num x) = [PUSH x]
compile (Add e1 e2) = compile e1 ++ compile e2 ++ [ADDI]
compile (Mult e1 e2) = compile e1 ++ compile e2 ++ [MULTI]

oneStep :: ([Int], [Instr]) -> ([Int], [Instr])
oneStep (s, PUSH i : r) = (i : s, r)
oneStep (v1 : v2 : s, ADDI : r) = ((v1 + v2) : s, r)
oneStep (v1 : v2 : s, MULTI : r) = ((v1 * v2) : s, r)

run :: ([Int], [Instr]) -> Int
run (v : s, []) = v
run (s, l) = run (oneStep (s, l))