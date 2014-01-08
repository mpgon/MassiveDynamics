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
    public class IntroducaoController : Controller
    {
        private ApplicationDbContext db = new ApplicationDbContext();

        // GET: /Introducao/
        public ActionResult Index()
        {
            return View(db.Introducao.ToList());
        }

        // GET: /Introducao/Details/5
        public ActionResult Details(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Introducao introducao = db.Introducao.Find(id);
            if (introducao == null)
            {
                return HttpNotFound();
            }
            return View(introducao);
        }

        // GET: /Introducao/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: /Introducao/Create
		// To protect from over posting attacks, please enable the specific properties you want to bind to, for 
		// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
		// 
		// Example: public ActionResult Update([Bind(Include="ExampleProperty1,ExampleProperty2")] Model model)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Create(Introducao introducao)
        {
            if (ModelState.IsValid)
            {
                db.Introducao.Add(introducao);
                db.SaveChanges();
                return RedirectToAction("Index");
            }

            return View(introducao);
        }

        // GET: /Introducao/Edit/5
        public ActionResult Edit(int? id)
        {
            if (id == null)
            {
                return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Introducao introducao = db.Introducao.Find(id);
            if (introducao == null)
            {
                return HttpNotFound();
            }
            return View(introducao);
        }

        // POST: /Introducao/Edit/5
		// To protect from over posting attacks, please enable the specific properties you want to bind to, for 
		// more details see http://go.microsoft.com/fwlink/?LinkId=317598.
		// 
		// Example: public ActionResult Update([Bind(Include="ExampleProperty1,ExampleProperty2")] Model model)
        [HttpPost]
        [ValidateAntiForgeryToken]
        public ActionResult Edit(Introducao introducao)
        {
            if (ModelState.IsValid)
            {
                db.Entry(introducao).State = EntityState.Modified;
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            return View(introducao);
        }

        // GET: /Introducao/Delete/5
        public ActionResult Delete(int? id)
        {
            if (id == null)
            {
				return new HttpStatusCodeResult(HttpStatusCode.BadRequest);
            }
            Introducao introducao = db.Introducao.Find(id);
            if (introducao == null)
            {
                return HttpNotFound();
            }
            return View(introducao);
        }

        // POST: /Introducao/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public ActionResult DeleteConfirmed(int id)
        {
            Introducao introducao = db.Introducao.Find(id);
            db.Introducao.Remove(introducao);
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
