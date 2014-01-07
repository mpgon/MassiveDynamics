using System;
using System.Collections.Generic;
using System.Data;
using System.Data.Entity;
using System.Linq;
using System.Net;
using System.Web;
using System.Web.Mvc;
using SocialGameWebSite.Models;
using MassiveDynamicsWebSite.Models;

namespace SocialGameWebSite.Controllers
{
    public class HumorController : Controller
    {
        private ApplicationDbContext db = new ApplicationDbContext();

        // GET: /Humor/
        public ActionResult Index()
        {
            return View(db.Humor.ToList());
        }

        // GET: /Humor/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Humor humor = db.Humor.Find(id);
            if (humor == null)
            {
                return HttpNotFound();
            }
            return View(humor);
        }

        // GET: /Humor/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: /Humor/Create
		// To protect from over posting attacks, please enable the specific properties you want to bind to, for 
		// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
		// 
		// Example: public ActionResult Update([Bind(Include="ExampleProperty1,ExampleProperty2")] Model model)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(Humor humor)
        {
            if (ModelState.IsValid)
            {
                db.Humor.Add(humor);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(humor);
        }

        // GET: /Humor/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Humor humor = db.Humor.Find(id);
            if (humor == null)
            {
                return HttpNotFound();
            }
            return View(humor);
        }

        // POST: /Humor/Edit/5
		// To protect from over posting attacks, please enable the specific properties you want to bind to, for 
		// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
		// 
		// Example: public ActionResult Update([Bind(Include="ExampleProperty1,ExampleProperty2")] Model model)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(Humor humor)
        {
            if (ModelState.IsValid)
            {
                db.Entry(humor).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(humor);
        }

        // GET: /Humor/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
				return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Humor humor = db.Humor.Find(id);
            if (humor == null)
            {
                return HttpNotFound();
            }
            return View(humor);
        }

        // POST: /Humor/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Humor humor = db.Humor.Find(id);
            db.Humor.Remove(humor);
            db.SaveChanges();
            return RedirectToAction("Index");
        }

        protected override void Dispose(bool disposing)
        {
            db.Dispose();
            base.Dispose(disposing);
        }
    }
}
