package demo

fun getGreeting(): String {
    val words = mutableListOf<String>()
    words.add("Hello,")
    words.add("world!")

    return words.joinToString(separator = " ")
}

fun loop() {
    val items = listOf("apple", "banana", "kiwi")
    for (item in items) {
        println(item)
    }
    for (index in items.indices) {
        println("item at $index is ${items[index]}")
    }
}

fun describe(obj: Any): String = 
when (obj) {
    1 -> "One"
    "Hello" -> "Greeting"
    is Long -> "Long"
    !is String -> "Not a String"
    else -> "Unknown"
}

fun testWhen() {
    println(describe(1));
    println(describe("Hello"));
    println(describe(100));
    println(describe(true));
}

fun testRange() {
    val x = 10
    val y = 9
    if (x in 1..y+1) {
        println("fit in range")
    }
}

interface Clickable {
    fun click()
    fun showOff() = println("I'm clickable!")
}

interface Focusable {
    fun setFocus(b: Boolean) = println("I ${if (b) "got" else "lost"} focus.")
    fun showOff() = println("I'm focusable!")
}

class Button : Clickable, Focusable {
    override fun click() = println("I was clicked")
    override fun showOff() {
        super<Clickable>.showOff()
        super<Focusable>.showOff()
    }
}

// open, final and abstract
open class RichButton: Clickable {
    // fun disable() {}
    open fun animate() {}
    final override fun click() {}
}

/*
class TestRichButton : RichButton {
    // override fun disable() {}
    override fun animate() {}
    override fun click() {}
}
*/

abstract class Animate {
    abstract fun animate()
    open fun stopAnimate() {}
    fun animateTwice() {}
}

/*
class TestAnimate : Animate {
    override fun animate() {}
    override fun stopAnimate() {}
    override fun animateTwice() {}
}
*/

// visibility modifiers
internal open class TalkativeButton : Focusable {
    private fun yell() = println("Hey!")
    protected fun whisper() = println("Let's talk!")
}

/*
fun TalkativeButton.giveSpeech() {
    yell()
    whisper()
}
*/

// sealed class
sealed class Expr {
    class Num(val value: Int) : Expr()
    class Sum(val left: Expr, val right: Expr) : Expr()
}

fun eval(e: Expr) : Int = 
    when (e) {
        is Expr.Num -> e.value
        is Expr.Sum -> eval(e.right) + eval(e.left)
    }

// 4.2.1 Initializing classes: primary constructor and initializer blocks
class User(val nickname: String, val isSubscribed: Boolean = true)

// open class User(val nickname: String)
// class TwitterUser(nickname: String): User(nickname)

class Secretive {
    private constructor()
}

// TODO: 4.2.2 Secondary constructors: initializing the superclass in different ways

// 4.2.3 Implementing properties declared in interfaces
interface IUser {
    val nickname: String
}

interface IEmailUser {
    val email: String
    val nickname: String
        get() = email.substringBefore('@')
}

class PrivateUser(override val nickname: String): IUser
class SubscribingUser(val email: String): IUser {
    override val nickname: String
        get() = email.substringBefore('@')
}
class GmailUser(override val email: String): IEmailUser

// 4.2.4 Accessing a backing field from a getter or setter

class BUser(val name: String) {
    var address: String = "unspecified"
        set(value: String) {
            println("""
                Address was changed for $name:
                "$field" -> "$value".""".trimIndent())
            field = value
        }
}

// =======================================================
fun main(args: Array<String>) {
    println(getGreeting())

    loop()
    testWhen()
    testRange()

    val button = Button()
    button.showOff()
    button.setFocus(true)
    button.click()

    val alice = User("Alice")
    println(alice.isSubscribed)
    val bob = User("Bob", false)
    println(bob.isSubscribed)

    // Cannot access '<init>': it is 'private' in 'Secretive'
    // val secretive = Secretive()

    println(PrivateUser("one@g.com").nickname)
    println(SubscribingUser("one@g.com").nickname)
    println(GmailUser("gmail@g.com").nickname)

    val balice =BUser("Alice")
    balice.address = "3233 E 7th Ave"
}