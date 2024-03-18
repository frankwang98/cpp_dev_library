package com.example.java_springboot.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class DemoController {

//    http://localhost:8080/hello
//    http://localhost:8080/hello?nickname=zhangsan&phone=123
//    @GetMapping("/hello")
    @RequestMapping(value = "/hello", method = RequestMethod.GET)
    public String hello(String nickname, String phone) {
        System.out.println(phone);
        return "你好" + nickname;
    }

}

