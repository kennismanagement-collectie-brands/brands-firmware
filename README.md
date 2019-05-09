# Knowledge Management Museum Collectie Brands


___

# Table of Content
## * 1.) Code Conventions
## * 2.) Repository Management

___

# 1.) Code Conventions
## 1.1) Naming
Use descriptive names for all identifiers (names of classes, variables and methods). Avoid ambiguity. Avoid abbreviations. 

* Descriptive naming.
* No abbreviations.
* Class names start with a capital letter.
* Class names are singular nouns.
* Methods and variable names start with lowercase letters. 



Examples:
### Naming methods
#### Set example
```csharp
 	accessModifier void setSomething(String[] variables);
```

#### Get example
```csharp
 	accessModifier dataType getSomething(String[] variables);
```

#### Boolean check example
```csharp
 	accessModifier bool isSomething(String[] variables);
```


### Naming variables
#### Class scope variable definition
A class scoped variable should always be provided with a prefix of 'm_'. The letter 'm' indicates that it is a member variable which is available within the scope of the instantiated class object.

```csharp
public class ExampleClass
{
	// Class variable(s)
	private int m_definedVariable = 0;

	public ExampleClass ()
	{
		// Constructor Implementation goes here
	}
}
```

#### Method scope variable definitions
```csharp
A method scoped variable can just be defined without the usage of any prefix.
public class ExampleClass
{
	public ExampleClass ()
	{
		// Constructor Implementation goes here
	}

	public void localScopeExample ()
	{
		// Method variable(s)
		int definedVariable = 0;
	}
}
```

## 1.2) Layout
Here's a summary of all the layout conventions:

* One level of indentation equals four spaces.
* Use a space before the opening brace of a control structure's block.
* Use a space after the name of a method or class.
* Use a space around operators.
* All statements within a block are intended one level.
* Braces for classes and methods are alone on one line.
* Braces for classes and methods are alone on one line.
* Other blocks (while, if, switches etc.) require one enter after the block definition.
* Other block's (while, if, switches etc.) braces have the same indentation level.
* Always use braces in control structures, therefore braces are used in if-statements and loops even if the body is only a single statement. 
* Use a blank line between methods (and constructors / destructors). Use blank lines to separate logical blocks of code. This means at least between methods, but also between logical parts within a method.

### Examples
#### Usage of spacing
```csharp
				// Note the space between 'ExampleClass' and the '()'
public ExampleClass () 
{
	int value = 1;
	// Note the spaces between the 'while', '()' and the opening brace.
	while () {

	}

	if () {

	// Note the spaces between the closing brace, 'else' notation and the opening brace.
	} else {

	}

	// Note the space between the operator
	value = value + 1;
	// NOTE: Preferred way is 'value += 1;' or 'value++;' this is just a depication of usage of spacing with operators.  
}
```
#### Braces for classes and methods
Braces for classes and methods are alone on one line.
Class example:
```csharp
public ExampleClass () 
{
	// Body goes here
}
```

Methods example:
```csharp
public void ExampleMethod ()
{
	// Body goes here
}
```

#### Layout for other blocks
Other blocks require one enter after the block definition. Braces should have the same indentation level as the block definition.
```csharp
public void ExampleMethod ()
{
	while (true) {
		// Statements
	}

	if (true) {
		// Statements
	} else {
		// Statements
	}
}
```

___

# 2.) Repository Management
## 2.1) Committing work
### Commit Conventions
For [commit conventions][1], please refer to the following [link][1].
### Pull requests
Each merge should be performed via a pull-request. Forcing the branch to be checked by another project member, thus ensuring quality and set requirements are met.

### Merge requests
Merging is only allowed via a pull request!

## 2.2)GitFlow
For each repository the [GitFlow][2] should be applied.




[1]: https://chris.beams.io/posts/git-commit/
[2]: https://www.atlassian.com/git/tutorials/comparing-workflows/gitflow-workflow