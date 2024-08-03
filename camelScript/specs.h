#include <array>
#include <cstdint>
#include <string>
#include <iostream>
#include <utility>
#include <map>




namespace cS {

	struct Token {

		enum Type {
			none,

			//operators
			opAdd, opSub, opMult, opDiv,
			opIncr, opDecr,
			opOr, opAnd, opXor, opNot,

			//equal signs
			Equal, Less, More,
			equalEqual, equalLess, equalMore, equalNot,

			//keywords
			kwAny,
			kwVariable, kwFunction, kwType,
			kwIf, kwReturn,
			kwMatch, kwTry, kwCatch, kwException,

			//symbols
			sbArrow, sbAnd, sbOr, sbSemicolon,
			sbParenthesisLeft, sbParenthesisRight, sbBraceLeft, sbBraceRight,
			sbCommentOneL, sbCommentManyStart, sbCommentManyEnd,

			//literals
			litBool, litInteger, litFloat, litChar, litString,
			litVariable, litFunction, litType, litPatternMatched,

		};
		Type tokenType;

		std::wstring tokenDetails;

		union {
			bool tokenBoolVal;
			int tokenIntVal;
			float tokenFloatVal;
			wchar_t tokenCharVal;
		};

		int lineNr;
		int characterNr;

		void log() const {

			switch (tokenType) {

			case(Type::none):
				std::cout << "NONE \n"; break;

				//operators
			case(Type::opSub):
				std::cout << "operator: Addition [ + ] \n"; break;
			case(Type::opAdd):
				std::cout << "operator: Substraction [ - ] \n"; break;
			case(Type::opMult):
				std::cout << "operator: Multiplication [ * ] \n"; break;
			case(Type::opDiv):
				std::cout << "operator: Division [ / ] \n"; break;
			case(Type::opIncr):
				std::cout << "operator: Increment [ ++ ] \n"; break;
			case(Type::opDecr):
				std::cout << "operator: Decrement [ -- ] \n"; break;
			case(Type::opOr):
				std::cout << "operator: Or [ || / or ] \n"; break;
			case(Type::opAnd):
				std::cout << "operator: And [ && / and ] \n"; break;
			case(Type::opXor):
				std::cout << "operator: Xor [ ^^ / xor ] \n"; break;
			case(Type::opNot):
				std::cout << "operator: Not [ ! / not ] \n"; break;

				//equal signs
			case(Type::Equal):
				std::cout << "sign: Equal [ = ] \n"; break;
			case(Type::Less):
				std::cout << "sign: Less [ < ] \n"; break;
			case(Type::More):
				std::cout << "sign: More [ > ] \n"; break;
			case(Type::equalEqual):
				std::cout << "sign: DoubleEqual [ == ] \n"; break;
			case(Type::equalLess):
				std::cout << "sign: Less or Equal [ >= ] \n"; break;
			case(Type::equalMore):
				std::cout << "sign: More or Equal [ >= ] \n"; break;
			case(Type::equalNot):
				std::cout << "sign: Not Equal [ != ] \n"; break;

				//keywords
			case(Type::kwAny):
				std::cout << "keyword: any [ any / _ ] \n"; break;
			case(Type::kwVariable):
				std::cout << "keyword: Variable(define) [ var ]\n"; break;
			case(Type::kwFunction):
				std::cout << "keyword: Function(define) [ fun ]\n"; break;
			case(Type::kwType):
				std::cout << "keyword: Type(define) [ type ]\n"; break;
			case(Type::kwIf):
				std::cout << "keyword: If [ if ]\n"; break;
			case(Type::kwReturn):
				std::cout << "keyword: Return [ return ]\n"; break;
			case(Type::kwMatch):
				std::cout << "keyword: Match [ match ]\n"; break;
			case(Type::kwTry):
				std::cout << "keyword: Try [ try ]\n"; break;
			case(Type::kwCatch):
				std::cout << "keyword: Catch [ catch ]\n"; break;
			case(Type::kwException):
				std::cout << "keyword: Exception [ exception ]\n"; break;


				//symbols
			case(Type::sbArrow):
				std::cout << "symbol: Arrow [ -> ]\n"; break;
			case(Type::sbAnd):
				std::cout << "symbol: And [ & ]\n"; break;
			case(Type::sbOr):
				std::cout << "symbol: Or [ | ]\n"; break;
			case(Type::sbSemicolon):
				std::cout << "symbol: Semicolon [ ; ]\n"; break;
			case(Type::sbParenthesisLeft):
				std::cout << "symbol: Left Parenthesis [ ( ]\n"; break;
			case(Type::sbParenthesisRight):
				std::cout << "symbol: Right Parenthesis [ ) ]\n"; break;
			case(Type::sbBraceLeft):
				std::cout << "symbol: Left Brace [ { ]\n"; break;
			case(Type::sbBraceRight):
				std::cout << "symbol: Right Brace [ } ]\n"; break;
			case(Type::sbCommentOneL):
				std::cout << "symbol: Comment(rest of the line) [ // / # ]\n"; break;
			case(Type::sbCommentManyStart):
				std::cout << "symbol: Comment Start [ /* ]\n"; break;
			case(Type::sbCommentManyEnd):
				std::cout << "symbol: Comment End [ */ ]\n"; break;

				//literals
			case(Type::litBool):
				std::wcout << "literal: Bool [ " << tokenBoolVal << " ]\n"; break;
			case(Type::litInteger):
				std::wcout << "literal: Integer [ " << tokenIntVal << " ]\n"; break;
			case(Type::litFloat):
				std::wcout << "literal: Float [ " << tokenFloatVal << " ]\n"; break;
			case(Type::litChar):
				std::wcout << "literal: Char [ \'" << tokenCharVal << "\' ]\n"; break;
			case(Type::litString):
				std::wcout << "literal: String [ \"" << tokenDetails << "\" ]\n"; break;
			case(Type::litVariable):
				std::wcout << "literal: Variable [ " << tokenDetails << " ]\n"; break;
			case(Type::litFunction):
				std::wcout << "literal: Function [ " << tokenDetails << " ]\n"; break;
			case(Type::litType):
				std::wcout << "literal: Type [ " << tokenDetails << " ]\n"; break;
			case(Type::litPatternMatched):
				std::wcout << "literal: Type Matched [ " << tokenDetails << " ]\n"; break;
			default:
				std::cout << "not implemented \n"; break;

			}
		}
	};

	static const std::map<std::wstring, Token::Type> OperatorsSignsSymbols{
		//operators
		{L"+", Token::Type::opAdd},{L"-", Token::Type::opSub},
		{L"*", Token::Type::opMult},{L"/", Token::Type::opDiv},
		{L"++", Token::Type::opIncr},{L"--", Token::Type::opDecr},
		{L"||", Token::Type::opOr},{L"&&", Token::Type::opAnd},//for now: without "and", "or"
		{L"^^", Token::Type::opXor},{L"!", Token::Type::opNot},
		//signs
		{L"=", Token::Type::Equal},{L"<", Token::Type::Less},
		{L">", Token::Type::More},{L"==", Token::Type::equalEqual},
		{L"=<", Token::Type::equalLess},{L">=", Token::Type::equalMore},
		{L"!=", Token::Type::equalNot},
		//symbols
		{L"->", Token::Type::sbArrow},{L"&", Token::Type::sbAnd},
		{L"|", Token::Type::sbOr},{L";", Token::Type::sbSemicolon},
		{L"(", Token::Type::sbParenthesisLeft},{L")", Token::Type::sbParenthesisRight},
		{L"{", Token::Type::sbBraceLeft},{L"}", Token::Type::sbBraceRight},
		{L"//", Token::Type::sbCommentOneL},{L"#", Token::Type::sbCommentOneL},
		{L"/*", Token::Type::sbCommentManyStart},{L"*/", Token::Type::sbCommentManyEnd}
	};

	static const std::map<std::wstring, Token::Type> Keywords{
		{L"any", Token::Type::kwAny},{L"_", Token::Type::kwAny},
		{L"var", Token::Type::kwVariable},{L"fun", Token::Type::kwFunction},
		{L"type", Token::Type::kwType},{L"if", Token::Type::kwIf},
		{L"return", Token::Type::kwReturn},{L"match", Token::Type::kwMatch},
		{L"try", Token::Type::kwTry},{L"catch", Token::Type::kwCatch},
		{L"exception", Token::Type::kwException}
		
	};
}
