fn main() {
    let v = vec![1, 2, 3];
    let v: Vec<i32> = Vec::new();
    let mut v = Vec::with_capacity(10);

    v.push(4);

    v.extend([5, 6].iter().cloned());

    match v.get(0) {
        Some(x) => println!("{}", x),
        None => println!("No element")
    };

    v[0];   // panic if invalid index

    let last = v.pop();
    let last = v.remove(0)

    v.len();
    v.is_empty();

    // iter
    for i in v.iter() {
        println!("{}", i);
    }

    // into_iter
    for i in v.into_iter() {
        println!("{}", i);
    }

    // iter_mut
    for i in v.iter_mut() {
        println!("{}", i);
    }
}