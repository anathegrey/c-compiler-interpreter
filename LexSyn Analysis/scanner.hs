import Data.Char

data Token
      = TokenInt Int
      | TokenPlus
      | TokenTimes
 deriving Show

lexer :: String -> [Token]
lexer [] = []
lexer (c : r)
      | isDigit c = lexNum (c : r)
      | isSpace c = lexer r
lexer ('+' : r) = TokenPlus : (lexer r)
lexer ('*' : r) = TokenTimes : (lexer r)

lexNum :: String -> [Token]
lexNum [] = []
lexNum l = let (a, b) = span isDigit l
	 in TokenInt (read a) : lexer b


