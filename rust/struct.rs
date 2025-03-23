#[derive(Debug)]
struct User {
    username: String,
    email: String
}

/*
    struct 实例声明mut, 则所有field 都可变
*/

// tuple struct
struct Color(i32, i32, i32);

fn build_user(email: String, username: String) -> User {
    User {
        email,
        username
    }
}

fn create_user(user: User, email: String) -> User {
    User {
        email,
        ..user
    }
}

fn main() {
    println!("Hello world");
    let user1 = User {
        email: String::from("HighVorz@outlook.com"),
        username: String::from("HighVorz")
    };

    let user2 = create_user(user1, String::from("hhh@outlook.com"));
    println!("user2: {:?}", user2);

    let color = Color(0, 0, 0);
}