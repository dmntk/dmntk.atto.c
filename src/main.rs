use crate::plane::Plane;
use std::fs;

mod plane;

fn main() {
  let file_name = "./examples/e1.dtb";
  let content = fs::read_to_string(file_name).unwrap();
  let plane = Plane::new(content);
  println!("{}", plane);
}
