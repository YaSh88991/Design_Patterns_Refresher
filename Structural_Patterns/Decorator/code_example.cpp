// ========== Violation: Using Inheritance ==========

#include <iostream>
#include <string>

// Base Post class
class Post
{
public:
    virtual std::string getContent() const = 0;
    virtual ~Post() {}
};

class BasicPost : public Post
{
public:
    std::string getContent() const override
    {
        return "Hello, world!";
    }
};

// Add a Tag using inheritance (rigid)
class TaggedPost : public BasicPost
{
public:
    std::string getContent() const override
    {
        return BasicPost::getContent() + " [#summer]";
    }
};

// Add a Feature using inheritance (explodes with combinations)
class FeaturePost : public BasicPost
{
public:
    std::string getContent() const override
    {
        return BasicPost::getContent() + " [Pinned]";
    }
};

// Problem : What if we want a post with tag + feature? More subclasses needed!

// ========== Decorator Pattern Proper ==========

// Decorator base class
class PostDecorator : public Post
{
protected:
    Post *post;

public:
    PostDecorator(Post *p) : post(p) {}
    virtual ~PostDecorator() { delete post; }
};

class TagDecorator : public PostDecorator
{
public:
    TagDecorator(Post *p) : PostDecorator(p) {}
    std::string getContent() const override
    {
        return post->getContent() + " [#summer]";
    }
};

class FeatureDecorator : public PostDecorator
{
public:
    FeatureDecorator(Post *p) : PostDecorator(p) {}
    std::string getContent() const override
    {
        return post->getContent() + " [Pinned]";
    }
};

// Usage
int main()
{
    // Rigid inheritance
    Post *p1 = new TaggedPost();
    std::cout << "TaggedPost (Inheritance): " << p1->getContent() << std::endl;
    delete p1;

    // Decorator: Add features dynamically
    Post *basic = new BasicPost();
    Post *withTag = new TagDecorator(basic);
    Post *withFeature = new FeatureDecorator(withTag); // Decorators can stack!

    std::cout << "Decorated Post: " << withFeature->getContent() << std::endl;

    delete withFeature; // Will delete all wrapped objects

    return 0;
}
